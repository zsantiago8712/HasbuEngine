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
    static unsigned int createVAO();
    static unsigned int createVBO(std::span<Vertex> vertices);
    static unsigned int createEBO(std::span<unsigned int> indices);

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

private:
    static RenderManager& getInstance();
    RenderManager();
    Utils::Unique<ApiContext::RenderData> m_data;
};

}
