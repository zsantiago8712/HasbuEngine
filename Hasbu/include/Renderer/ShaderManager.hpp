#pragma once
#include "Utilities/DynamicAllocator.hpp"

namespace Hasbu::ApiContext {

struct ShaderData;

}

namespace Hasbu::Render {

class ShaderManager {

public:
    static unsigned int createShader(const std::string_view& vsFile, const std::string_view& fsFile);
    static void deleteShader(unsigned int& id);

    static void bind(const unsigned int id);
    static void unBind();

    static void setInt(const unsigned int id, const std::string_view& uniformName, const int data);
    static void setFloat(const unsigned int id, const std::string_view& uniformName, const float data);

    static void setVec3(const unsigned int id, const std::string_view& uniformName, const float* data);
    static void setM4f(const unsigned int id, const std::string_view& uniform_name, const float* data);

private:
    ShaderManager();
    static ShaderManager& getInstance();

    Utils::Unique<ApiContext::ShaderData> m_data;
};

}
