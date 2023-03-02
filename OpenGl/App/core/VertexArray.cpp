#include "VertexArray.hpp"
#include "Glad/glad.h"

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

}