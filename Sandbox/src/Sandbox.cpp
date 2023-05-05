#include <core/Entrypoint.hpp>

class Sandbox : public Hasbu::App {

public:
    Sandbox() = default;

    ~Sandbox() = default;
};

Hasbu::App* Hasbu::createApplication()
{
    return new Sandbox();
}