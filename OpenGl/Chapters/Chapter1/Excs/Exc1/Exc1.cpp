#include <core/Application.hpp>

int main()
{
    hasbu::App app;
    app.init();
    app.run_ex1("OpenGL/Chapters/Chapter1/Exc1/Exc1.vs",
        "OpenGL/Chapters/Chapter1/Exc1/Exc1.fs");
}