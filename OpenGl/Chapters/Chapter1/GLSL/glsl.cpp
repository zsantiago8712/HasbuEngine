#include <core/Application.hpp>

int main()
{
    hasbu::App app;
    app.init();
    app.run("OpenGL/Chapters/Chapter1/GLSL/GLSL.vs", "OpenGL/Chapters/Chapter1/GLSL/GLSL.fs");
}