#include <core/Application.hpp>

int main()
{
    hasbu::App app;
    app.init();
    app.run("OpenGL/Chapters/Chapter1/HelloTriangle/hello_triangle.vs", "OpenGL/Chapters/Chapter1/HelloTriangle/hello_triangle.fs");
}