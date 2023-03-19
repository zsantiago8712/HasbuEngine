#pragma once
#include "core/Application.hpp"

extern Hasbu::App* Hasbu::createApplication();

int main(int argc, const char** argv)
{
    auto app = Hasbu::createApplication();
    app->init();
    app->run("Chapters/Chapter1/3D/3D.vs", "Chapters/Chapter1/3D/3D.fs");
    delete app;
}