#include "ShaderManager.hpp"
#include <Glad/glad.h>
#include <fmt/core.h>
#include <fstream>
#include <sstream>
#include <string_view>

void check_shader(const int id_shader);
void check_link(const unsigned int id_program);

namespace Hasbu {

Shader::Shader(std::string_view const& shader_name)
{
    if (this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} already exists\n", shader_name);
        return;
    }
    const unsigned int shader_program_id = glCreateProgram();
    this->tb_shaders.try_emplace(shader_name, shader_program_id);
}

void Shader::insert(const std::string_view& shaderName)
{
    if (this->tb_shaders.contains(shaderName)) {
        fmt::print("Error: Shader {} already exists!!\n", shaderName);
        return;
    }

    const unsigned int new_shader_id = glCreateProgram();
    this->tb_shaders.try_emplace(shaderName, new_shader_id);
}

unsigned int Shader::getShaderId(const std::string_view& shader_name) const
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return 0;
    }

    return this->tb_shaders.at(shader_name);
}

void Shader::compile_shaders(std::string_view const& shader_name, std::string_view const& vertex_shader_file_source, std::string_view const& fragment_shader_file_source)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print(stderr, "Shader not found: {}. Please create before trying to compile\n\n", shader_name);
        return;
    }

    const unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    const unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    const std::string vertex_data = Shader::get_shader_from_file(vertex_shader_file_source);
    const std::string fragment_data = Shader::get_shader_from_file(fragment_shader_file_source);

    const char* vertex_shader = vertex_data.c_str();
    const char* fragment_shader = fragment_data.c_str();

    glShaderSource(vertex_shader_id, 1, &vertex_shader, nullptr);
    glCompileShader(vertex_shader_id);
    check_shader(vertex_shader_id);
    glAttachShader(this->tb_shaders.at(shader_name), vertex_shader_id);

    glShaderSource(fragment_shader_id, 1, &fragment_shader, nullptr);
    glCompileShader(fragment_shader_id);
    check_shader(fragment_shader_id);
    glAttachShader(this->tb_shaders.at(shader_name), fragment_shader_id);

    glLinkProgram(this->tb_shaders.at(shader_name));
    check_link(this->tb_shaders.at(shader_name));
}

void Shader::bind(std::string_view const& shader_name)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return;
    }

    glUseProgram(this->tb_shaders.at(shader_name));
}

void Shader::unbind(std::string_view const& shader_name)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return;
    }

    glUseProgram(0);
    this->tb_shaders.erase(shader_name);
}

std::string Shader::get_shader_from_file(std::string_view const& filename)
{
    std::ifstream shader_file(filename.data());
    if (!shader_file.good()) {
        fmt::print("Shader File {} not found!!\n", filename);
        exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << shader_file.rdbuf();

    return buffer.str();
}

void Shader::setUniformF(const std::string_view& shader_name, std::string_view const& uniform_name, const float value)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return;
    }

    glUniform1f(glGetUniformLocation(this->tb_shaders.at(shader_name), uniform_name.data()), value);
}

void Shader::setUniformI(const std::string_view& shader_name, std::string_view const& uniform_name, const int value)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return;
    }

    glUniform1i(glGetUniformLocation(this->tb_shaders.at(shader_name), uniform_name.data()), value);
}

void Shader::setUniformM4f(const std::string_view& shader_name, const std::string_view& uniform_name, const float* values)
{
    if (!this->tb_shaders.contains(shader_name)) {
        fmt::print("Shader {} does not exists\n", shader_name);
        return;
    }
    glUniformMatrix4fv(glGetUniformLocation(this->tb_shaders.at(shader_name), uniform_name.data()), 1, GL_FALSE, values);
}

}

void check_shader(const int id_shader)
{
    int succes;
    glGetShaderiv(id_shader, GL_COMPILE_STATUS, &succes);

    if (!succes) {
        char info_log[512];
        glGetShaderInfoLog(id_shader, 512, nullptr, info_log);
        fmt::print(stderr, "Comipile error: {}\n", info_log);
        exit(EXIT_FAILURE);
    }
}

void check_link(const unsigned int id_program)
{
    int success;
    glGetProgramiv(id_program, GL_LINK_STATUS, &success);

    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(id_program, 512, nullptr, info_log);
        fmt::print(stderr, "Link error: {}\n", info_log);
        exit(EXIT_FAILURE);
    }
}