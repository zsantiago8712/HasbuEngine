#pragma once
#include "Utilities/DynamicAllocator.hpp"
#include "Vertex.hpp"
#include <span>

namespace Hasbu::ApiContext {

struct RenderData;

};

namespace Hasbu::Render {

enum class VertexAttrib {
    POSITIONS = 0,
    NORMALS = 1,
    TEXTURES_COORDS = 2,
};

class RenderManager {
public:
    static void createRenderContext();

    static void clearWindow(const float red = 0.2f, const float green = 0.3f, const float blue = 0.3f, const float alpha = 1.0f);

    static void drawElements(const unsigned int size);
    static void drawElementsBaseVertex(const unsigned int size, const unsigned int baseVertex);

    static unsigned int createVAO();
    static unsigned int createVBO();
    static unsigned int createEBO();

    static unsigned int createVBO(const std::span<Vertex> vertives);
    static unsigned int createEBO(const std::span<unsigned int> indices);

    static unsigned int createDynamicVBO();
    static unsigned int createDynamicEBO();

    static unsigned int createDynamicVBO(const std::span<Vertex> vertives);
    static unsigned int createDynamicEBO(const std::span<unsigned int> indices);

    static unsigned int createDynamicInstanceVBO();

    static void bindVAO(const unsigned int id);
    static void bindVBO(const unsigned int id);
    static void bindEBO(const unsigned int id);

    static void unbindVAO();
    static void unbindVBO();
    static void unbindEBO();

    static void destroyVAO(unsigned int& id);
    static void destroyVBO(unsigned int& id);
    static void destroyEBO(unsigned int& id);

    static void attribPointer(VertexAttrib attrib);

    static void addDataVBO(const unsigned int id, const std::span<Vertex> vertices);
    static void addDataEBO(const unsigned int id, const std::span<unsigned> indices);

    static void updateDataVBO(const unsigned int id, const unsigned int vertexCount, const std::span<Vertex> vertices);
    static void updateDataEBO(const unsigned int id, const unsigned int indexCount, const std::span<unsigned int> indices);

    static void checkError(const char* file, const int line);
    static double getDeltaTime();
    static double getLastDelta();

    enum class API {
        GL = 0X0,
        VK = 0X1,
    };
    static API m_api;

private:
    static double m_lastFrame;
    static double m_deltaTime;
};

#ifdef DEBUG
#define CHECK_ERROR() Hasbu::Render::RenderManager::checkError(__FILE__, __LINE__);
#else
#define CHECK_ERROR()
#endif // DEBUG

}
