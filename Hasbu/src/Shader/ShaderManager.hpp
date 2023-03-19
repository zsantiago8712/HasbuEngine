#pragma once
#include <string_view>
#include <unordered_map>

namespace Hasbu {

class Shader {

public:
    explicit Shader(std::string_view const& shaderName);

    void insert(std::string_view const& shaderName);
    void compile_shaders(std::string_view const& shader_name, std::string_view const& vertex_shader_file_source, std::string_view const& fragment_shader_file_source);

    void bind(std::string_view const& shader_name);
    void unbind(std::string_view const& shader_name);
    unsigned int getShaderId(std::string_view const& shader_name) const;

    void setUniformF(std::string_view const& shader_name, std::string_view const& uniform_name, float value);
    void setUniformI(std::string_view const& shader_name, std::string_view const& uniform_name, int values);
    void setUniformM4f(std::string_view const& shader_name, std::string_view const& uniform_name, const float* values);

private:
    static std::string get_shader_from_file(std::string_view const& file_name);
    std::unordered_map<std::string_view, unsigned int> tb_shaders;
};

}
