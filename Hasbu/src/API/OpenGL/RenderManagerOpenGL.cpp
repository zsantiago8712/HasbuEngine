#include "Application/Window.hpp"
#include "Renderer/RenderManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

namespace Hasbu::Render {

constexpr std::size_t MAX_VERTEX_SIZE = 100 * 1000 * 5000 * sizeof(Render::Vertex);
constexpr std::size_t MAX_INSTANCE_VERTEX_SIZE = 100 * 1000 * 5000 * sizeof(glm::mat4);
constexpr std::size_t MAX_INDICES_SIZE = 1'000'000 * sizeof(unsigned int);

double RenderManager::m_lastFrame = 0.0f;
double RenderManager::m_deltaTime = 0.0f;
RenderManager::API RenderManager::m_api = RenderManager::API::GL;

void RenderManager::createRenderContext()
{
    HASBU_ASSERT(GLEW_OK != glewInit(), "GLEW (OpenGL) failed to load")

    glEnable(GL_DEPTH_TEST);

    HASBU_INFO("OPENGL succes to load {}", reinterpret_cast<const char*>((glGetString(GL_VERSION))));
}

void RenderManager::clearWindow(const float red, const float green, const float blue, const float alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::drawElements(const unsigned int size)
{
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
    CHECK_ERROR()
}

void RenderManager::drawElementsBaseVertex(const unsigned int size, const unsigned int baseVertex)
{
    glDrawElementsBaseVertex(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 0), baseVertex);
}

unsigned int RenderManager::createVAO()
{
    unsigned int newVAO = 0;
    glGenVertexArrays(1, &newVAO);
    glBindVertexArray(newVAO);
    CHECK_ERROR()

    return newVAO;
}

unsigned int RenderManager::createVBO()
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ARRAY_BUFFER, newVBO);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createEBO()
{
    unsigned int newEBO = 0;
    glGenBuffers(1, &newEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
    CHECK_ERROR()

    return newEBO;
}

unsigned int RenderManager::createVBO(const std::span<Vertex> vertices)
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ARRAY_BUFFER, newVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createEBO(const std::span<unsigned int> indices)
{
    unsigned int newEBO = 0;
    glGenBuffers(1, &newEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    CHECK_ERROR()

    return newEBO;
}

unsigned int RenderManager::createDynamicVBO()
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ARRAY_BUFFER, newVBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_SIZE, nullptr, GL_DYNAMIC_DRAW);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createDynamicEBO()
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES_SIZE, nullptr, GL_STATIC_DRAW);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createDynamicVBO(const std::span<Vertex> vertices)
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ARRAY_BUFFER, newVBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_SIZE, nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices[0]);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createDynamicEBO(const std::span<unsigned int> indices)
{
    unsigned int newVBO = 0;
    glGenBuffers(1, &newVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES_SIZE, &indices[0], GL_STATIC_DRAW);
    CHECK_ERROR()

    return newVBO;
}

unsigned int RenderManager::createDynamicInstanceVBO()
{
    unsigned int newInstanceVBO = 0;
    glGenBuffers(1, &newInstanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, newInstanceVBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCE_VERTEX_SIZE, nullptr, GL_DYNAMIC_DRAW);
    CHECK_ERROR()

    return newInstanceVBO;
}

void RenderManager::bindVAO(const unsigned int vao)
{
    glBindVertexArray(vao);
    CHECK_ERROR()
}

void RenderManager::bindVBO(const unsigned int vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    CHECK_ERROR()
}

void RenderManager::bindEBO(const unsigned int ebo)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    CHECK_ERROR()
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

void RenderManager::destroyVAO(unsigned int& vao)
{
    glDeleteVertexArrays(1, &vao);
}

void RenderManager::destroyVBO(unsigned int& vbo)
{
    glDeleteBuffers(1, &vbo);
}

void RenderManager::destroyEBO(unsigned int& ebo)
{
    glDeleteBuffers(1, &ebo);
}

void RenderManager::addDataVBO(const unsigned int vbo, const std::span<Vertex> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    CHECK_ERROR()
}

void RenderManager::addDataEBO(const unsigned int ebo, const std::span<unsigned> indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    CHECK_ERROR()
}

void RenderManager::updateDataVBO(const unsigned int vbo, const unsigned int vertexCount, const std::span<Vertex> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    CHECK_ERROR()
    glBufferSubData(GL_ARRAY_BUFFER, vertexCount, sizeof(Vertex) * vertices.size(), &vertices[0]);
    CHECK_ERROR()
}

void RenderManager::updateDataEBO(const unsigned int ebo, const unsigned int indexCount, const std::span<unsigned int> indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    CHECK_ERROR()
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexCount, sizeof(unsigned int) * indices.size(), &indices[0]);
    CHECK_ERROR()
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
    RenderManager::m_deltaTime = current_time - m_lastFrame;
    m_lastFrame = current_time;
    return RenderManager::m_deltaTime;
}

double RenderManager::getLastDelta()
{
    return RenderManager::m_deltaTime;
}

void RenderManager::checkError(const char* file, const int line)
{
    unsigned int severity;
    do {
        severity = glGetError();
        if (severity != GL_NO_ERROR) {
            switch (severity) {
            case GL_INVALID_ENUM:
                HASBU_ERROR("[OPENGL]: INVALID_ENUM [FILE: {}; LINE: {}]", file, line);
                break;
            case GL_INVALID_VALUE:
                HASBU_ERROR("[OPENGL]: INVALID_VALUE [FILE: {}; LINE: {}]", file, line);
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
            default:
                HASBU_DEBUG("opengl: error codde {}", severity);
                break;
            }
        }

    } while (severity != GL_NO_ERROR);
}

}