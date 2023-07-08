#include "Renderer/MeshManager.hpp"
#include "Renderer/RenderManager.hpp"
#include "Vertex.hpp"
#include <span>

namespace Hasbu::Render {

unsigned int MeshManager::nextMeshID = 0;

unsigned int MeshManager::createDynamicMesh(Components::RenderComponents& components, const std::span<Vertex> vertices, const std::span<unsigned int> indices)
{
    components.vao = RenderManager::createVAO();
    components.vbo = RenderManager::createDynamicVBO(vertices);
    components.ebo = RenderManager::createDynamicEBO(indices);

    RenderManager::attribPointer(VertexAttrib::POSITIONS);
    RenderManager::attribPointer(VertexAttrib::NORMALS);
    RenderManager::attribPointer(VertexAttrib::TEXTURES_COORDS);

    return nextMeshID++;
}

unsigned int MeshManager::createDynamicMesh(Components::RenderComponents& components)
{
    components.vao = RenderManager::createVAO();
    components.vbo = RenderManager::createDynamicVBO();
    components.ebo = RenderManager::createDynamicEBO();

    RenderManager::attribPointer(VertexAttrib::POSITIONS);
    RenderManager::attribPointer(VertexAttrib::NORMALS);
    RenderManager::attribPointer(VertexAttrib::TEXTURES_COORDS);

    return nextMeshID++;
}

unsigned int MeshManager::createStaticMesh(Components::RenderComponents& components, const std::span<Vertex> vertices, const std::span<unsigned int> indices)
{
    components.vao = RenderManager::createVAO();
    components.vbo = RenderManager::createVBO(vertices);
    components.ebo = RenderManager::createEBO(indices);

    RenderManager::attribPointer(VertexAttrib::POSITIONS);
    RenderManager::attribPointer(VertexAttrib::NORMALS);
    RenderManager::attribPointer(VertexAttrib::TEXTURES_COORDS);

    return nextMeshID++;
}

unsigned int MeshManager::createStaticMesh(Components::RenderComponents& components)
{
    components.vao = RenderManager::createVAO();
    components.vbo = RenderManager::createVBO();
    components.ebo = RenderManager::createEBO();

    RenderManager::attribPointer(VertexAttrib::POSITIONS);
    RenderManager::attribPointer(VertexAttrib::NORMALS);
    RenderManager::attribPointer(VertexAttrib::TEXTURES_COORDS);

    return nextMeshID++;
}

}