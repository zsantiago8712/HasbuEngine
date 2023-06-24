#include "FileManager.hpp"
#include "Renderer/Shader.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>
#include <string_view>

static void compileShader(const unsigned int& id);
static void linkProgram(const unsigned int& id_program);

namespace HasbuAPIContext {

struct ShaderDataApi {
    unsigned int id;
};

unsigned int creataProgram(void)
{
    return glCreateProgram();
}

void createShader(unsigned int& id_program, const std::string_view& vs_file, const std::string_view& fs_file)
{

    const unsigned int vs_id = glCreateShader(GL_VERTEX_SHADER);
    const unsigned int fs_id = glCreateShader(GL_FRAGMENT_SHADER);

    const auto vs_data = HasbuUtils::loadShader(vs_file);
    const auto fs_data = HasbuUtils::loadShader(fs_file);

    const char* c_vs_data = vs_data.c_str();
    const char* c_fs_data = fs_data.c_str();

    glShaderSource(vs_id, 1, &c_vs_data, nullptr);
    glShaderSource(fs_id, 1, &c_fs_data, nullptr);

    compileShader(vs_id);
    compileShader(fs_id);

    id_program = glCreateProgram();

    glAttachShader(id_program, vs_id);
    glAttachShader(id_program, fs_id);

    linkProgram(id_program);
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

void bindProgram(const unsigned int& id_program)
{
    glUseProgram(id_program);
}

void unBindProgram(void)
{
    glUseProgram(0);
}

}

static void compileShader(const unsigned int& id)
{
    int succes;

    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &succes);

    if (!succes) {
        char info_log[512];
        glGetShaderInfoLog(id, 512, nullptr, info_log);
        HASBU_FATAL("Something wrong during Shader compilation {}", info_log);
        exit(-1);
    }

    HASBU_INFO("Shader {} compile succesfuly", id);
}

static void linkProgram(const unsigned int& id_program)
{
    int succes;
    glLinkProgram(id_program);

    glGetProgramiv(id_program, GL_LINK_STATUS, &succes);

    if (!succes) {
        char info_log[512];
        glGetProgramInfoLog(id_program, 512, nullptr, info_log);
        HASBU_FATAL("Something wrong during Program linking {}", info_log);
        exit(-1);
    }

    HASBU_INFO("Program {} linked succesfuly", id_program);
}

namespace HasbuRender {

Shader::Shader()
{
    this->data = HasbuUtils::createShared<HasbuAPIContext::ShaderDataApi>();
}

void Shader::create(const std::string_view& vs_file, const std::string_view& fs_file)
{
    HasbuAPIContext::createShader(this->data->id, vs_file, fs_file);
}

void Shader::bind() const
{
    glUseProgram(this->data->id);
    // HasbuAPIContext::bindProgram(this->data->id);
}

void Shader::unBind() const
{
    HasbuAPIContext::unBindProgram();
}

Shader::~Shader()
{
    this->data.reset();
}

void Shader::setInt(const std::string_view& uniform_name, const int& data)
{
    auto x = glGetUniformLocation(this->data->id, uniform_name.data());
    glUniform1i(x, data);
}

void Shader::setM4f(const std::string_view& uniform_name, const float* data)
{
    glUniformMatrix4fv(glGetUniformLocation(this->data->id, uniform_name.data()), 1, GL_FALSE, data);
}

}
