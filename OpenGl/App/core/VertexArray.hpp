#pragma once

namespace hasbu {

class VertexArray {
public:
    VertexArray();
    void bind() const;

private:
    unsigned int vao_id;
};

}