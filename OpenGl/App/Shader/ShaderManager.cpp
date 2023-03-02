#include "ShaderManager.hpp"
#include "Glad/glad.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <utility>

void check_shader(const int id_shader);
void check_link(const unsigned int id_program);

namespace hasbu {

Shader::Shader(std::string_view const& shader_name)
{
    if (this->tb_shaders.contains(shader_name)) {
        std::cout << "Shader " << shader_name << " already exists\n";
        return;
    }
    const unsigned int shader_program_id = glCreateProgram();
    this->tb_shaders.try_emplace(shader_name, shader_program_id);
}

void Shader::compile_shader(std::string_view const& shader_name, std::string_view const& shader_file_source, TypeShader type) const
{
    // TODO: read file and pass it to this function

    if (!this->tb_shaders.contains(shader_name)) {
        std::cerr << "Shader not found: " << shader_file_source << ". Please create before trying to compile\n";
    }

    const unsigned int vf_shader_id = glCreateShader(static_cast<unsigned int>(type));

    const std::string data = this->get_shader_from_file(shader_file_source).data();
    const char* content = data.c_str();

    glShaderSource(vf_shader_id, 1, &content, nullptr);
    glCompileShader(vf_shader_id);

    check_shader(vf_shader_id);
    glAttachShader(this->tb_shaders.at(shader_name), vf_shader_id);
    glLinkProgram(this->tb_shaders.at(shader_name));

    check_link(this->tb_shaders.at(shader_name));
    glDeleteShader(vf_shader_id);
}

void Shader::bind(std::string_view const& shader_name)
{
    if (!this->tb_shaders.contains(shader_name)) {
        std::cerr << "Shader " << shader_name << " does not exist\n";
        return;
    }

    glUseProgram(this->tb_shaders.at(shader_name));
}

void Shader::unbind(std::string_view const& shader_name)
{
    if (!this->tb_shaders.contains(shader_name)) {
        std::cerr << "Shader " << shader_name << " does not exist\n";
        return;
    }

    glUseProgram(0);
    this->tb_shaders.erase(shader_name);
}

std::string Shader::get_shader_from_file(std::string_view const& filename) const
{
    std::ifstream shader_file(filename.data());
    if (!shader_file.good()) {
        std::cerr << "SHADER FILE " << filename << " NOT FOUND!\n";
        exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << shader_file.rdbuf();

    return buffer.str();
}

}

void check_shader(const int id_shader)
{
    int succes;

    glGetShaderiv(id_shader, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        std::string infoLog;
        glGetShaderInfoLog(id_shader, 512, nullptr, infoLog.data());
        std::cerr << infoLog.data() << "\n";
        exit(EXIT_FAILURE);
    }
}

void check_link(const unsigned int id_program)
{
    int success;

    glGetProgramiv(id_program, GL_LINK_STATUS, &success);

    if (!success) {
        std::string info_log;
        glGetProgramInfoLog(id_program, 512, nullptr, info_log.data());
        std::cerr << info_log.data() << "\n";
        exit(EXIT_FAILURE);
    }
}