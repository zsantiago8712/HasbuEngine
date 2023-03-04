#include <core/Application.hpp>

int main()
{
    hasbu::App app;
    app.init();
    app.run_ex2("OpenGL/Chapters/Chapter1/Exc2/Exc2.vs",
        "OpenGL/Chapters/Chapter1/Exc2/Exc2.fs");
}