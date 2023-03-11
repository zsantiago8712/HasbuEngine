#pragma once
#include <vector>

namespace hasbu {

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    bool normalized;
};

class VertexBufferLayout {

public:
    VertexBufferLayout() = default;

    const std::vector<VertexBufferElement>& getElements() const;
    unsigned int getStride() const;

    template <typename T>
    void push(unsigned int cont);

    static unsigned int getSizeOfType(unsigned int type);

private:
    unsigned int stride = 0;
    std::vector<VertexBufferElement> elements;
};

}