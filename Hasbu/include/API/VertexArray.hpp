#pragma once
#include "Utilities/DynamicAllocator.hpp"
#include "Renderer/Vertex.hpp"

namespace HasbuAPIContext {

struct VertexArrayData;





enum class VertexAttrib {
    POSITIONS = 0,
    TEXTURES_COORDS = 1,
    NORMALS = 2,
};



struct VertexArray {

    HasbuUtils::Shared<VertexArrayData> data;

    void create(const std::span<HasbuRender::Vertex> vertices, const std::span<unsigned int> indices);

    void bind();
    void unBindVertexArray();
    void attribPointer(VertexAttrib attrib, const std::size_t& size = 3);

};


}
