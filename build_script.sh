#!/bin/bash

# Define el directorio raíz del proyecto
project_root=$(pwd)

# Verifica el número de argumentos
if [ $# -lt 2 ]; then
    echo "Uso: $0 <build_type> <api>"
    exit 1
fi

# Obtiene los argumentos
build_type=$1
api=$2
verb=$3

# Verifica el tipo de compilación y establece el directorio raíz correspondiente
if [ "$1" == "D" ]; then
    build_type="Debug";
    cmake_root="${project_root}/build_debug"
    elif [ "$1" == "R" ]; then
    build_type="Release";
    cmake_root="${project_root}/build_release"
    
else
    echo "Error: build_type debe ser D (para Debug) o R (para Release)"
    exit 1
fi


if [ "$api" = "O" ]; then
    
    # echo "No support yet for OpenGL"
    # exit 1;
    cmake_root="${cmake_root}_opengl"
    # Ejecuta el comando de configuración de CMake
    cmake -DCMAKE_BUILD_TYPE="${build_type}" -DUSE_OPENGL=ON -DUSE_VULKAN=OFF -H"${project_root}" -B"${cmake_root}" -G Ninja;
    elif [ "$api" = "V" ]; then
    echo "Using Vulkan SH"
    cmake_root="${cmake_root}_vulkan"
    # Ejecuta el comando de configuración de CMake
    
    cmake -DCMAKE_BUILD_TYPE="${build_type}" -DUSE_OPENGL=OFF -DUSE_VULKAN=ON -H"${project_root}" -B"${cmake_root}" -G Ninja;
else
    echo "Error: api debe ser O (para OpenGL) o V (para Vulkan)"
    exit 1
fi

# Ejecuta el comando make para compilar el proyecto en el directorio de compilación correspondiente
if [ "$verb" = "V" ]; then
    ninja -C"${cmake_root}" --verbose;
else
    ninja -C"${cmake_root}";
fi

# Para vscode se genera el archivo compile_commands.json
cp "${cmake_root}/compile_commands.json" .;
