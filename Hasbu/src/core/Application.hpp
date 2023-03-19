#pragma once
#include "core/Window.hpp"
#include "defines.hpp"
#include <string_view>

namespace Hasbu {

class App {
public:
    App() = default;
    void init();
    void run(std::string_view const& vertex_shader_file, std::string_view const& fragment_shader_file);

private:
    Unique<Window> m_Window;
};

App* createApplication();
}