#include "ElementBuffer.hpp"
#include "Glad/glad.h"

namespace hasbu {

ElementBuffer::ElementBuffer(const unsigned int* indices, const unsigned int size)
{
    glGenBuffers(1, &this->ebo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_id);
}

}