#include "DynamicAllocator.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Utilities/FileManager.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>
#include <array>

static void compileShader(const unsigned int id);
static void linkProgram(const unsigned int id_program);

namespace Hasbu::ApiContext {

struct ShaderData {

    Utils::Vector<std::array<const char*, 2>> shaderFiles;
    Utils::Vector<unsigned int> ids;
};

}

namespace Hasbu::Render {

ShaderManager::ShaderManager()
    : m_data(Utils::createUnique<ApiContext::ShaderData>()) {};

ShaderManager& ShaderManager::getInstance()
{
    static ShaderManager manager;
    return manager;
}

unsigned int ShaderManager::createShader(const std::string_view& vsFile, const std::string_view& fsFile)
{
    const unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
    const unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

    const auto vsData = Utils::loadShader(vsFile);
    const auto fsData = Utils::loadShader(fsFile);

    const char* cVsData = vsData.c_str();
    const char* cFsData = fsData.c_str();

    glShaderSource(vsID, 1, &cVsData, nullptr);
    glShaderSource(fsID, 1, &cFsData, nullptr);

    compileShader(vsID);
    compileShader(fsID);

    const unsigned int programID = glCreateProgram();

    glAttachShader(programID, vsID);
    glAttachShader(programID, fsID);

    linkProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(fsID);

    auto& manager = ShaderManager::getInstance();
    manager.m_data->ids.push_back(programID);
    manager.m_data->shaderFiles.push_back({ vsFile.data(), fsFile.data() });
    return static_cast<unsigned int>(manager.m_data->ids.size());
}

void ShaderManager::deleteShader(unsigned int& id)
{
    auto& manager = ShaderManager::getInstance();
    glDeleteShader(manager.m_data->ids[id - 1]);

    manager.m_data->ids.erase(manager.m_data->ids.begin() + (id - 1));
    manager.m_data->shaderFiles.erase(manager.m_data->shaderFiles.begin() + (id - 1));

    id = 0;
}

void ShaderManager::reaload()
{

    const auto& manager = ShaderManager::getInstance();
    const auto size = manager.m_data->ids.size();

    for (unsigned int i = 0; i < size; i++) {
        
        const unsigned int programID = manager.m_data->ids[i];

        const unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
        const unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

        const auto vsData = Utils::loadShader(manager.m_data->shaderFiles[i][0]);
        const auto fsData = Utils::loadShader(manager.m_data->shaderFiles[i][1]);

        const char* cVsData = vsData.c_str();
        const char* cFsData = fsData.c_str();

        glShaderSource(vsID, 1, &cVsData, nullptr);
        glShaderSource(fsID, 1, &cFsData, nullptr);

        compileShader(vsID);
        compileShader(fsID);


        glUseProgram(0);
        glDetachShader(programID, vsID);
        glDetachShader(programID, fsID);

        glAttachShader(programID, vsID);
        glAttachShader(programID, fsID);

        linkProgram(programID);
        glDeleteShader(vsID);
        glDeleteShader(fsID);

    }
}

void ShaderManager::bind(const unsigned int id)
{
    auto& manager = ShaderManager::getInstance();
    glUseProgram(manager.m_data->ids[id - 1]);
}

void ShaderManager::unBind()
{
    glUseProgram(0);
}

void ShaderManager::setInt(const unsigned int id, const std::string_view& uniformName, const int data)
{
    const auto& manager = ShaderManager::getInstance();
    glUniform1i(glGetUniformLocation(manager.m_data->ids[id - 1], uniformName.data()), data);
}

void ShaderManager::setFloat(const unsigned int id, const std::string_view& uniformName, const float data)
{
    const auto& manager = ShaderManager::getInstance();
    glUniform1f(glGetUniformLocation(manager.m_data->ids[id - 1], uniformName.data()), data);
}

void ShaderManager::setVec3(const unsigned int id, const std::string_view& uniformName, const float* data)
{
    const auto& manager = ShaderManager::getInstance();
    glUniform3fv(glGetUniformLocation(manager.m_data->ids[id - 1], uniformName.data()), 1, data);
}

void ShaderManager::setM4f(const unsigned int id, const std::string_view& uniformName, const float* data)
{
    const auto& manager = ShaderManager::getInstance();
    glUniformMatrix4fv(glGetUniformLocation(manager.m_data->ids[id - 1], uniformName.data()), 1, GL_FALSE, data);
}

}

static void compileShader(const unsigned int id)
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

static void linkProgram(const unsigned int id_program)
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
