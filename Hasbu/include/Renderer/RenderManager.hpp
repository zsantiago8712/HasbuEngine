#pragma once
#include "Utilities/DynamicAllocator.hpp"
#include "Vertex.hpp"

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
    static unsigned int createVBO(const std::span<Vertex> vertices);
    static unsigned int createEBO(const std::span<unsigned int> indices);

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

    static void checkError(const char* file, const int line);
    static double getDeltaTime();

    enum class API {
        GL = 0X0,
        VK = 0X1,
    };
    API m_api;

private:
    static RenderManager& getInstance();
    RenderManager();

    static double m_lastFrame;
    Utils::Unique<ApiContext::RenderData> m_data;
};

#define CHECK_ERROR() Hasbu::Render::Renderer::checkError(__FILE__, __LINE__);

}
