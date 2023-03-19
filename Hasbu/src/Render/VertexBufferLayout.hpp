#pragma once

#include "defines.hpp"
#include <initializer_list>
#include <vector>

namespace Hasbu {

enum class BufferElementType {

    FLOAT = 0x0,
    FLOAT_2 = 0x1,
    FLOAT_3 = 0x02,
    FLOAT_4 = 0x3,

    UNSIGNED_INT = 0x4,
    UNSIGNED_INT_2 = 0x5,
    UNSIGNED_INT_3 = 0x6,
    UNSIGNED_INT_4 = 0x7,

    UNSIGNED_CHAR = 0x8,
    UNSIGNED_CHAR_2 = 0x9,
    UNSIGNED_CHAR_3 = 0x11,
    UNSIGNED_CHAR_4 = 0x12,
};

struct VertexBufferElement {
    BufferElementType type;
    unsigned int count;
    bool normalized;
    unsigned int offset = 0;
    VertexBufferElement(BufferElementType type, bool normalized = false);
};

struct VertexBufferLayout {
    VertexBufferLayout() = default;
    explicit VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);
    std::vector<VertexBufferElement> m_BufferElements;
    unsigned int m_Stride = 0;
};

void createVertexBufferLayout(VertexBufferLayout& layout);

// class VertexBufferLayout {

// public:
//     VertexBufferLayout() = default;
//     explicit VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements);
//     ~VertexBufferLayout() = default;

//     const std::vector<VertexBufferElement>& getElements() const;
//     unsigned int m_Stride = 0;

// private:
//     std::vector<VertexBufferElement> m_BufferElements;

//     void calculateStride();
// };

}