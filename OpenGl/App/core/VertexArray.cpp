#include "VertexArray.hpp"
#include "core/VertexBufferLayout.hpp"
#include <Glad/glad.h>

namespace hasbu {

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->vao_id);
    glBindVertexArray(this->vao_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(this->vao_id);
}

void VertexArray::addBuffer(const VertexBufferLayout& layout) const
{
    auto elements = layout.getElements();
    const auto stride = layout.getStride();
    unsigned int offset = 0;

    for (int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (void*)offset);
        glEnableVertexAttribArray(i);

        offset += element.count * VertexBufferLayout::getSizeOfType(element.type);
    }
    this->bind();
}

}