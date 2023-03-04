#pragma once
#include <Window/Window.hpp>

namespace hasbu {

class App {
public:
    App() = default;
    void init();
    void run(std::string_view const& vertex_shader_file, std::string_view const& fragment_shader_file);

private:
    Window window;
};

}