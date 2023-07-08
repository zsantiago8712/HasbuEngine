#include "Application/EntityManager.hpp"
#include "Components/MaterailComponents.hpp"
#include "Components/MeshComponents.hpp"
#include "Renderer/MeshManager.hpp"
#include "Renderer/TextureManager.hpp"
#include "ShaderManager.hpp"
#include "Utilities/Logger.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iterator>

void loadModel(const std::string_view& modelFile, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures);
void processNode(const std::string_view& dir, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures, aiNode* node, const aiScene* scene);
void loadMaterialTexture(const std::string_view& dir, Hasbu::Utils::Vector<unsigned int>& textures, aiMaterial* material, aiTextureType type, Hasbu::Render::TextureType textureType);
void processMesh(const std::string_view& dir, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures, aiMesh* mesh, const aiScene* scene);

namespace Hasbu::Render {

unsigned int createModelEntity(const std::string_view& vsShaderFile, const std::string_view& fsShaderFile)
{
    auto& entityManager = Core::EntityManager::getInstance();
    entt::entity newModelEntity = entityManager.registry.create();

    entityManager.registry.emplace<Components::MeshComponents>(newModelEntity);
    entityManager.registry.emplace<Components::RenderComponents>(newModelEntity);
    entityManager.registry.emplace<Components::MaterialComponents>(newModelEntity);

    auto& materialComponents = entityManager.registry.get<Components::MaterialComponents>(newModelEntity);
    materialComponents.shaderID = ShaderManager::createShader(vsShaderFile, fsShaderFile);

    materialComponents.vsShader = vsShaderFile;
    materialComponents.fsShader = fsShaderFile;

    return static_cast<unsigned int>(newModelEntity);
}

unsigned int createStaticModelEntity()
{
    auto& entityManager = Core::EntityManager::getInstance();
    entt::entity newModelEntity = entityManager.registry.create();

    entityManager.registry.emplace<Components::MeshComponents>(newModelEntity);
    entityManager.registry.emplace<Components::RenderComponents>(newModelEntity);

    return static_cast<unsigned int>(newModelEntity);
}

void loadDynamicModelFromFile(const unsigned int modelID, const std::string_view& modelFile)
{
    auto& entityManager = Core::EntityManager::getInstance();
    auto& meshComponents = entityManager.registry.get<Components::MeshComponents>(static_cast<entt::entity>(modelID));
    auto& renderComponents = entityManager.registry.get<Components::RenderComponents>(static_cast<entt::entity>(modelID));
    auto& materialComponents = entityManager.registry.get<Components::MaterialComponents>(static_cast<entt::entity>(modelID));

    Utils::Vector<Vertex> vertices;
    Hasbu::Utils::Vector<unsigned int> indices;

    loadModel(modelFile, meshComponents, indices, materialComponents.textures);
    vertices.reserve(meshComponents.totalVertexCount);
    for (const auto& vertex : meshComponents.vertices) {
        vertices.insert(vertices.end(), std::make_move_iterator(vertex.begin()), std::make_move_iterator(vertex.end()));
    }
    meshComponents.meshID = MeshManager::createDynamicMesh(renderComponents, vertices, indices);
}

void loadStaticModelFromFile(const unsigned int modelID, const std::string_view& modelFile)
{
    auto& entityManager = Core::EntityManager::getInstance();
    auto& meshComponents = entityManager.registry.get<Components::MeshComponents>(static_cast<entt::entity>(modelID));
    auto& renderComponents = entityManager.registry.get<Components::RenderComponents>(static_cast<entt::entity>(modelID));
    auto& materialComponents = entityManager.registry.get<Components::MaterialComponents>(static_cast<entt::entity>(modelID));

    Utils::Vector<Vertex> vertices;
    Hasbu::Utils::Vector<unsigned int> indices;

    loadModel(modelFile, meshComponents, indices, materialComponents.textures);
    vertices.reserve(meshComponents.totalVertexCount);
    for (const auto& vertex : meshComponents.vertices) {
        vertices.insert(vertices.end(), std::make_move_iterator(vertex.begin()), std::make_move_iterator(vertex.end()));
    }
    meshComponents.meshID = MeshManager::createStaticMesh(renderComponents, vertices, indices);
}

const Components::MaterialComponents& getModelMaterialComponents(const unsigned int modelID)
{
    auto& entityManager = Core::EntityManager::getInstance();
    return entityManager.registry.get<Components::MaterialComponents>(static_cast<entt::entity>(modelID));
}

}

void loadModel(const std::string_view& modelFile, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFile.data(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    HASBU_ASSERT(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode, "ASSIMP ERROR")
    const std::string_view dir = modelFile.substr(0, modelFile.find_last_of('/'));

    processNode(dir, meshComponents, indices, textures, scene->mRootNode, scene);
}

void processNode(const std::string_view& dir, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(dir, meshComponents, indices, textures, mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(dir, meshComponents, indices, textures, node->mChildren[i], scene);
    }
}

void processMesh(const std::string_view& dir, Hasbu::Components::MeshComponents& meshComponents, Hasbu::Utils::Vector<unsigned int>& indices, Hasbu::Utils::Vector<unsigned int>& textures, aiMesh* mesh, const aiScene* scene)
{
    const auto baseVertexIndex = meshComponents.totalVertexCount;
    Hasbu::Utils::Vector<Hasbu::Render::Vertex> tempVertices;

    const auto numMesh = static_cast<unsigned int>(meshComponents.vertices.size());
    meshComponents.subMeshIds.push_back(numMesh);

    tempVertices.reserve(mesh->mNumVertices);
    meshComponents.vertices.emplace_back();
    meshComponents.vertices[numMesh].reserve(mesh->mNumVertices);
    meshComponents.totalVertexCount += mesh->mNumVertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

        const auto vertex = mesh->mVertices[i];
        glm::vec2 textureCoords { 0.0f, 0.0f };
        glm::vec3 normals { 0.0f, 0.0f, 0.0f };

        if (mesh->HasNormals()) {
            const auto normal = mesh->mNormals[i];
            normals = { normal.x, normal.y, normal.z };
        }

        if (mesh->mTextureCoords[0]) {
            const auto texture = mesh->mTextureCoords[0][i];
            textureCoords = { texture.x, texture.y };
        }

        tempVertices.push_back(
            { .m_position = { vertex.x, vertex.y, vertex.z },
                .m_normal = normals,
                .m_textCoords = textureCoords });
    }


    meshComponents.vertices[numMesh].insert(meshComponents.vertices[numMesh].end(), std::make_move_iterator(tempVertices.begin()), std::make_move_iterator(tempVertices.end()));
    unsigned int totalIndices = 0;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace face = mesh->mFaces[i];
        totalIndices += face.mNumIndices;
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(baseVertexIndex + face.mIndices[j]);
        }
    }

    meshComponents.indexCountBySubMesh.push_back(totalIndices);
    meshComponents.totalIndexCount += totalIndices;
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    loadMaterialTexture(dir, textures, material, aiTextureType_DIFFUSE, Hasbu::Render::TextureType::DIFFUSE);
    loadMaterialTexture(dir, textures, material, aiTextureType_SPECULAR, Hasbu::Render::TextureType::SPECULAR);
    loadMaterialTexture(dir, textures, material, aiTextureType_AMBIENT, Hasbu::Render::TextureType::HEIGHT);
    loadMaterialTexture(dir, textures, material, aiTextureType_HEIGHT, Hasbu::Render::TextureType::NORMAL);
}

void loadMaterialTexture(const std::string_view& dir, Hasbu::Utils::Vector<unsigned int>& textures, aiMaterial* material, aiTextureType type, Hasbu::Render::TextureType textureType)
{
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        const auto textureFile = fmt::format("{}/{}", dir, str.data);

        unsigned int textureID = Hasbu::Render::TextureManager::isLoaded(textureFile.data());

        if (textureID == 0) {
            textureID = Hasbu::Render::TextureManager::createTexture(textureFile, textureType);
            textures.push_back(textureID);
        }
        // textures.push_back(textureID);
    }
}
