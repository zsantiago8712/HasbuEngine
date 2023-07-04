#include "Application/Window.hpp"
#include "Renderer/RenderManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

static void createOpenGLContext();

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

double RenderManager::m_lastFrame = 0.0f;

RenderManager::RenderManager()
    : m_api(RenderManager::API::GL)
    , m_data(Utils::createUnique<ApiContext::RenderData>())
{
    createOpenGLContext();
};

void RenderManager::createRenderContext()
{
    getInstance();
}

RenderManager& RenderManager::getInstance()
{
    static RenderManager renderManager;
    return renderManager;
}

void RenderManager::clearWindow(const float red, const float green, const float blue, const float alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::drawElements(const unsigned int size)
{
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
}

void RenderManager::drawElementsBaseVertex(const unsigned int size,  const unsigned int baseVertex)
{
    glDrawElementsBaseVertex(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*) (sizeof(unsigned int) * 0), baseVertex);
}




unsigned int RenderManager::createVAO()
{
    unsigned int newVao = 0;
    ApiContext::createVertexArray(newVao);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->vao.push_back(newVao);
    return static_cast<unsigned int>(manager.m_data->vao.size());
}

unsigned int RenderManager::createVBO(const std::span<Vertex> vertices)
{
    unsigned int newVBO = 0;
    ApiContext::createVertexBuffer(newVBO, vertices);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->vbo.push_back(newVBO);
    return static_cast<unsigned int>(manager.m_data->vbo.size());
}

unsigned int RenderManager::createEBO(const std::span<unsigned int> indices)
{
    unsigned int newEBO = 0;
    ApiContext::createElementsVertexBuffer(newEBO, indices);

    RenderManager& manager = RenderManager::getInstance();

    manager.m_data->ebo.push_back(newEBO);

    return static_cast<unsigned int>(manager.m_data->ebo.size());
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

double RenderManager::getDeltaTime()
{
    const double current_time = Core::getTime();
    const double delta_time = current_time - m_lastFrame;
    m_lastFrame = current_time;
    return delta_time;
}

void RenderManager::checkError(const char* file, const int line)
{
    unsigned int severity;
    do {
        severity = glGetError();
        switch (severity) {
        case GL_INVALID_ENUM:
            HASBU_ERROR("[OPENGL]: INVALID_ENUM [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_VALUE:
            HASBU_ERROR("[OPENGL]: INVALID_VALUE [FILE: {}; LINE: {}], file, line");
            break;
        case GL_STACK_OVERFLOW:
            HASBU_WARNING("[OPENGL]: STACK_OVERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_OUT_OF_MEMORY:
            HASBU_ERROR("[OPENGL]: STACK_UNDERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_OPERATION [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_FRAMEBUFFER [FILE: {}; LINE: {}]", file, line);
            break;
        }
    } while (severity != GL_NO_ERROR);
}

}

static void createOpenGLContext()
{
    HASBU_ASSERT(GLEW_OK != glewInit(), "GLEW (OpenGL) failed to load")

    glEnable(GL_DEPTH_TEST);

    HASBU_INFO("OPENGL succes to load {}", reinterpret_cast<const char*>((glGetString(GL_VERSION))));
}
