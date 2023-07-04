#include "Renderer/ModelsManager.hpp"
#include "RenderManager.hpp"
#include "Renderer/MeshManager.hpp"
#include "Renderer/TextureManager.hpp"
#include "Utilities/DynamicAllocator.hpp"
#include "Utilities/Logger.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Hasbu::Render {

void processNode(Utils::Vector<unsigned int>& meshID, aiNode* node, const aiScene* scene);
void loadMaterialTexture(Utils::Vector<unsigned int>& textures, aiMaterial* material, aiTextureType type, Hasbu::Render::TextureType textureType);
unsigned int processMesh(aiMesh* mesh, const aiScene* scene);

struct ModelsManager {

    static ModelsManager& getInstance();
    static std::string_view getDirectory();

    Utils::Vector<Utils::Vector<unsigned int>> m_meshIDs;
    Utils::Vector<std::string_view> m_directories;
};

ModelsManager& ModelsManager::getInstance()
{
    static ModelsManager manager;
    return manager;
}

std::string_view ModelsManager::getDirectory()
{
    const auto& manager = ModelsManager::getInstance();
    const auto size = manager.m_directories.size() - 1;
    return manager.m_directories[size];
}

unsigned int loadModel(const std::string_view& fileModel)
{
    auto& manager = ModelsManager::getInstance();
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileModel.data(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

    HASBU_ASSERT(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode, "ASSIMP ERROR")

    const std::string_view dir = fileModel.substr(0, fileModel.find_last_of('/'));
    manager.m_directories.push_back(dir);

    Utils::Vector<unsigned int> temp;
    processNode(temp, scene->mRootNode, scene);
    manager.m_meshIDs.push_back(temp);

    return static_cast<unsigned int>(manager.m_directories.size());
}

void drawModel(const unsigned int modelID, const unsigned int shaderID)
{
    const auto& manager = ModelsManager::getInstance();
    for (const auto& meshID : manager.m_meshIDs[modelID - 1]) {
        drawMesh(meshID, shaderID);
    }
}

void processNode(Utils::Vector<unsigned int>& meshID, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshID.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(meshID, node->mChildren[i], scene);
    }
}

unsigned int processMesh(aiMesh* mesh, const aiScene* scene)
{
    Utils::Vector<Hasbu::Render::Vertex> vertices;
    Utils::Vector<unsigned int> indices;
    Utils::Vector<unsigned int> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

        const auto vertice = mesh->mVertices[i];
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

        vertices.push_back({ .m_position = { vertice.x, vertice.y, vertice.z },
            .m_normal = normals,
            .m_textCoords = textureCoords });
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    loadMaterialTexture(textures, material, aiTextureType_DIFFUSE, Hasbu::Render::TextureType::DIFFUSE);
    loadMaterialTexture(textures, material, aiTextureType_SPECULAR, Hasbu::Render::TextureType::SPECULAR);
    loadMaterialTexture(textures, material, aiTextureType_AMBIENT, Hasbu::Render::TextureType::HEIGHT);
    loadMaterialTexture(textures, material, aiTextureType_HEIGHT, Hasbu::Render::TextureType::NORMAL);

    return Hasbu::Render::createMesh(vertices, indices, textures);
}

void loadMaterialTexture(Utils::Vector<unsigned int>& textures, aiMaterial* material, aiTextureType type, Hasbu::Render::TextureType textureType)
{
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        const auto dir = Hasbu::Render::ModelsManager::getDirectory();
        const auto textureFile = fmt::format("{}/{}", dir, str.data);

        unsigned int textureID = Hasbu::Render::TextureManager::isLoaded(textureFile.data());

        if (textureID == 0) {
            textureID = Hasbu::Render::TextureManager::createTexture(textureFile, textureType);
        }
        textures.push_back(textureID);
    }
}
}
