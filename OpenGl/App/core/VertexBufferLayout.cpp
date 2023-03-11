#include "VertexBufferLayout.hpp"
#include <Glad/glad.h>
#include <fmt/core.h>

namespace hasbu {

template <typename T>
void VertexBufferLayout::push(const unsigned int count [[maybe_unused]])
{
    fmt::print(stderr, "ERROR: need to pass an especialitazion type of \n");
}

template <>
void VertexBufferLayout::push<float>(const unsigned int count)
{
    this->elements.emplace_back(VertexBufferElement { GL_FLOAT, count, false });
    this->stride += count * getSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(const unsigned int count)
{
    this->elements.emplace_back(VertexBufferElement { GL_UNSIGNED_INT, count, false });
    this->stride += count * getSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(const unsigned int count)
{
    this->elements.emplace_back(VertexBufferElement { GL_UNSIGNED_BYTE, count, false });
    this->stride += count * getSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
    return this->elements;
}

unsigned int VertexBufferLayout::getStride() const
{
    return this->stride;
}

unsigned int VertexBufferLayout::getSizeOfType(const unsigned int type)
{
    switch (type) {
    case GL_FLOAT:
        return 4;
        break;

    case GL_UNSIGNED_INT:
        return 4;
        break;

    case GL_UNSIGNED_BYTE:
        return 1;
        break;

    default:
        fmt::print("ERROR unknown type\n");
        exit(EXIT_FAILURE);
        break;
    }
}

}