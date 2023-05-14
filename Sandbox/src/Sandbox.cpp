#include "core/Application.hpp"
#include "defines.hpp"
#include <core/Entrypoint.hpp>

class Sandbox : public Hasbu::App {

public:
    Sandbox() = default;
    ~Sandbox() = default;
};

Hasbu::Unique<Hasbu::App> Hasbu::createApplication()
{
    return createUnique<Sandbox>();
}