#include <core/Application.hpp>

int main()
{
    hasbu::App app;
    app.init();
    app.run_ex3("OpenGL/Chapters/Chapter1/Exc3/Exc3.vs",
        "OpenGL/Chapters/Chapter1/Exc3/Exc3.fs");
}