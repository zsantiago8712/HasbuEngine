#include <core/Application.hpp>

int main()
{
    Hasbu::App app;
    app.init();
    app.run("OpenGL/Chapters/Chapter1/Textures/Tex.vs", "OpenGL/Chapters/Chapter1/Textures/Tex.fs");
}