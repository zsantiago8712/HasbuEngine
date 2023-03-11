#pragma once

#include "core/VertexBufferLayout.hpp"
namespace hasbu {

class VertexArray {
public:
    VertexArray();
    void bind() const;
    void addBuffer(VertexBufferLayout const& layout) const;

private:
    unsigned int vao_id;
};

}