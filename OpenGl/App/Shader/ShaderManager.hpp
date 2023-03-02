#pragma once
#include <string_view>
#include <unordered_map>

namespace hasbu {

enum class TypeShader : unsigned int {
    VERTEX_SHADER = 0x8B31,
    FRAGMENT_SHADER = 0x8B30,
};

class Shader {

public:
    explicit Shader(std::string_view const& shaderName);

    void compile_shader(std::string_view const& shader_name, std::string_view const& shader_file_source, TypeShader type) const;
    void bind(std::string_view const& shader_name);
    void unbind(std::string_view const& shader_name);

private:
    std::string get_shader_from_file(std::string_view const& file_name) const;
    std::unordered_map<std::string_view, unsigned int> tb_shaders;
    unsigned int program_id = -1;
    void check() const;
};

}
