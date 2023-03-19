#include "Render/VertexBufferLayout.hpp"
#include <Glad/glad.h>
#include <fmt/core.h>

namespace Hasbu {

static unsigned int getSizeOfType(BufferElementType type);
static GLenum getGLType(BufferElementType type);
static unsigned int getCount(BufferElementType type);
static void calculateStride(VertexBufferLayout& layout);

VertexBufferElement::VertexBufferElement(BufferElementType type, const bool normalized)
    : type(type)
    , count(getCount(type))
    , normalized(normalized) {};

VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements)
    : m_BufferElements(elements)
{
    calculateStride(*this);
}

void createVertexBufferLayout(VertexBufferLayout& layout)
{
    using enum Hasbu::BufferElementType;
    layout.m_BufferElements = {
        { FLOAT_3, false },
        { FLOAT_3, false },
        { FLOAT_2, false },
    };

    calculateStride(layout);
}

static void calculateStride(VertexBufferLayout& layout)
{
    unsigned int temp_offset = 0;
    for (auto& element : layout.m_BufferElements) {

        element.offset = temp_offset;
        layout.m_Stride += getSizeOfType(element.type);
        temp_offset += getSizeOfType(element.type);
    }
}

static GLenum getGLType(BufferElementType type)
{
    using enum BufferElementType;
    switch (type) {
    case FLOAT:
    case FLOAT_2:
    case FLOAT_3:
    case FLOAT_4:
        return GL_FLOAT;

    case UNSIGNED_INT:
    case UNSIGNED_INT_2:
    case UNSIGNED_INT_3:
    case UNSIGNED_INT_4:
        return GL_UNSIGNED_INT;

    case UNSIGNED_CHAR:
    case UNSIGNED_CHAR_2:
    case UNSIGNED_CHAR_3:
    case UNSIGNED_CHAR_4:
        return GL_UNSIGNED_BYTE;

    default:
        fmt::print("[ERROR] unknow type\n");
        return -1;
    }
}

static unsigned int getSizeOfType(BufferElementType type)
{
    using enum BufferElementType;
    switch (type) {

    case FLOAT:
    case UNSIGNED_INT:
    case UNSIGNED_CHAR_4:
        return 4;

    case FLOAT_2:
    case UNSIGNED_INT_2:
        return 4 * 2;

    case FLOAT_3:
    case UNSIGNED_INT_3:
        return 4 * 3;

    case UNSIGNED_INT_4:
    case FLOAT_4:
        return 4 * 4;

    case UNSIGNED_CHAR:
        return 1;
    case UNSIGNED_CHAR_2:
        return 2;
    case UNSIGNED_CHAR_3:
        return 3;

    default:
        fmt::print("[ERROR] unknow type\n");
        return 0;
    }
}

static unsigned int getCount(BufferElementType type)
{

    using enum BufferElementType;
    switch (type) {

    case FLOAT:
    case UNSIGNED_INT:
    case UNSIGNED_CHAR:
        return 1;

    case FLOAT_2:
    case UNSIGNED_INT_2:
    case UNSIGNED_CHAR_2:
        return 2;

    case FLOAT_3:
    case UNSIGNED_INT_3:
    case UNSIGNED_CHAR_3:
        return 3;

    case FLOAT_4:
    case UNSIGNED_INT_4:
    case UNSIGNED_CHAR_4:
        return 4;

    default:
        fmt::print("[ERROR] unknow type\n");
        return 0;
    }
}

// const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
// {
//     return m_BufferElements;
// }

}
