#include "DynamicAllocator.hpp"
#include "Renderer/RenderManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

namespace Hasbu::ApiContext {

struct RenderData {

    Utils::Vector<unsigned int> vao;
    Utils::Vector<unsigned int> vbo;
    Utils::Vector<unsigned int> ebo;
};

void createVertexArray(unsigned int& id)
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

void createVertexBuffer(unsigned int& id, std::span<Render::Vertex> vertices)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Render::Vertex), &vertices[0], GL_STATIC_DRAW);
}

void createElementsVertexBuffer(unsigned int& id, std::span<unsigned int> indices)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

}

namespace Hasbu::Render {

RenderManager::RenderManager()
    : m_data(Utils::createUnique<ApiContext::RenderData>()) {};

RenderManager& RenderManager::getInstance()
{
    static RenderManager renderManager;
    return renderManager;
}

unsigned int RenderManager::createVAO()
{
    unsigned int newVao = 0;
    ApiContext::createVertexArray(newVao);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->vao.push_back(newVao);
    return manager.m_data->vao.back();
}

unsigned int RenderManager::createVBO(std::span<Vertex> vertices)
{
    unsigned int newVBO = 0;
    ApiContext::createVertexBuffer(newVBO, vertices);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->vbo.push_back(newVBO);
    return manager.m_data->vbo.back();
}

unsigned int RenderManager::createEBO(std::span<unsigned int> indices)
{
    unsigned int newEBO = 0;
    ApiContext::createElementsVertexBuffer(newEBO, indices);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->ebo.push_back(newEBO);

    return manager.m_data->ebo.back();
}

void RenderManager::bindVAO(const unsigned int id)
{
    RenderManager& manager = RenderManager::getInstance();
    glBindVertexArray(manager.m_data->vao[id - 1]);
}

void RenderManager::bindVBO(const unsigned int id)
{
    RenderManager& manager = RenderManager::getInstance();
    glBindBuffer(GL_ARRAY_BUFFER, manager.m_data->vbo[id - 1]);
}

void RenderManager::bindEBO(const unsigned int id)
{
    RenderManager& manager = RenderManager::getInstance();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, manager.m_data->ebo[id - 1]);
}

void RenderManager::unbindVAO()
{
    glBindVertexArray(0);
}

void RenderManager::unbindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void RenderManager::unbindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderManager::destroyVAO(unsigned int& id)
{
    RenderManager& manager = RenderManager::getInstance();
    glDeleteVertexArrays(1, &manager.m_data->vao[id - 1]);
    manager.m_data->vao.erase(manager.m_data->vao.begin() + (id - 1));
    id = 0;
}

void RenderManager::destroyVBO(unsigned int& id)
{
    RenderManager& manager = RenderManager::getInstance();
    glDeleteBuffers(1, &manager.m_data->vbo[id]);
    manager.m_data->vbo.erase(manager.m_data->vbo.begin() + (id - 1));
    id = 0;
}

void RenderManager::destroyEBO(unsigned int& id)
{
    RenderManager& manager = RenderManager::getInstance();
    glDeleteBuffers(1, &manager.m_data->ebo[id]);
    manager.m_data->ebo.erase(manager.m_data->ebo.begin() + (id - 1));
    id = 0;
}

void RenderManager::attribPointer(VertexAttrib attrib)
{
    switch (attrib) {
    case VertexAttrib::POSITIONS:
        glVertexAttribPointer(static_cast<unsigned int>(attrib), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);
        break;

    case VertexAttrib::NORMALS:
        glVertexAttribPointer(static_cast<unsigned int>(attrib), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));
            glEnableVertexAttribArray(1);
        break;

    case VertexAttrib::TEXTURES_COORDS:
        glVertexAttribPointer(static_cast<unsigned int>(attrib), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_textCoords));
        glEnableVertexAttribArray(2);
        break;

    default:
        HASBU_FATAL("UNKNOW attribute type");
        return;
    }
}

}
