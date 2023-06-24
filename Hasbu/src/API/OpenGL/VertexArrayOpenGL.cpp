#include "API/VertexArray.hpp"
#include "Renderer/Context.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>
#include <span>

namespace HasbuAPIContext {

struct VertexArrayData {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    HasbuUtils::Vector<unsigned int> vertex_count;
    HasbuUtils::Vector<unsigned int> index_count;
};

// TODO: IMPLEMENTAR LAS PARTES DEL INDEX BUFFER
void VertexArray::create(const std::span<HasbuRender::Vertex> vertices, const std::span<unsigned int> indices)
{

    this->data = HasbuUtils::createShared<VertexArrayData>();

    // Create Buffers
    glGenVertexArrays(1, &this->data->vao);
    glGenBuffers(1, &this->data->vbo);
    glGenBuffers(1, &this->data->ebo);

    // Activate Buffers
    glBindVertexArray(this->data->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->data->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->data->ebo);

    // Set buffers data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(HasbuRender::Vertex), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void VertexArray::attribPointer(VertexAttrib attrib, const std::size_t& size)
{
    auto a = offsetof(HasbuRender::Vertex, text_coords);
    auto b = static_cast<unsigned int>(attrib);
    switch (attrib) {
    case VertexAttrib::POSITIONS:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(b, size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)0);
        break;

    case VertexAttrib::NORMALS:
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(static_cast<unsigned int>(attrib), size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)offsetof(HasbuRender::Vertex, normal));
        break;

    case VertexAttrib::TEXTURES_COORDS:
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(b, size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)a);
        break;
    default:
        HASBU_FATAL("UNKNOW attribute type");
        return;
    }
}

void VertexArray::bind()
{
    glBindVertexArray(this->data->vao);
}

void VertexArray::unBindVertexArray(void)
{
    glBindVertexArray(0);
}

void VertexAttribPointer(VertexAttrib attrib, const std::size_t size)
{
    auto a = offsetof(HasbuRender::Vertex, text_coords);
    auto b = static_cast<unsigned int>(attrib);
    switch (attrib) {
    case VertexAttrib::POSITIONS:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(b, size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)0);
        break;

    case VertexAttrib::NORMALS:
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(static_cast<unsigned int>(attrib), size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)offsetof(HasbuRender::Vertex, normal));
        break;

    case VertexAttrib::TEXTURES_COORDS:
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(b, size, GL_FLOAT, GL_FALSE, sizeof(HasbuRender::Vertex), (void*)a);
        break;
    default:
        HASBU_FATAL("UNKNOW attribute type");
        return;
    }
}

}
