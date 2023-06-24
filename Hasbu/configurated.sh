#!/bin/bash
carpetas="API Application Renderer"

for carpeta in $carpetas
do
    cp ~/Developer/OpenGL/Hasbu/src/"$carpeta/CMakeLists.txt" src/"$carpeta";
done

