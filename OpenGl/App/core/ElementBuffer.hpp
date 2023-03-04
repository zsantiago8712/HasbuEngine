#pragma once

namespace hasbu {

class ElementBuffer {

public:
    ElementBuffer(const unsigned int* indices, const unsigned int size);
    void bind() const;

private:
    unsigned int ebo_id;
};

}