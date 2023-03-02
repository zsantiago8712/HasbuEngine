#pragma once

namespace hasbu {

class VertexBuffer {
private:
    unsigned int vbo_id;

public:
    explicit VertexBuffer(const void* data, unsigned int size);
    void bind() const;
    void unbind() const;
};

}