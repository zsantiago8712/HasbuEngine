#pragma once
#include "Renderer/Vertex.hpp"
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::ApiContext {
struct VertexArrayData;
}

namespace Hasbu::Render {

enum class VertexAttrib {
    POSITIONS = 0,
    TEXTURES_COORDS = 1,
    NORMALS = 2,
};

struct VertexArray {

    Utils::Shared<ApiContext::VertexArrayData> data;

    void create(const std::span<Vertex> vertices, const std::span<unsigned int> indices);
    void bind() const;
    void unBindVertexArray() const;
    void attribPointer(VertexAttrib attrib, const std::size_t& size = 3);
};
}
