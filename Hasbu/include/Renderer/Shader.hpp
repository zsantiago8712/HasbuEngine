#pragma once

#include "Utilities/DynamicAllocator.hpp"
#include <string_view>

namespace Hasbu::ApiContext {
struct ShaderDataApi;
}

namespace Hasbu::Render {

struct Shader {

    explicit Shader();
    ~Shader();

    void create(const std::string_view& vs_file, const std::string_view& fs_file);
    void bind() const;
    void unBind() const;

    void setInt(const std::string_view& uniform_name, const int data) const;
    void setFloat(const std::string_view& uniformName, const float data) const;

    void setVec3(const std::string_view& uniformName, const float* data) const;
    void setM4f(const std::string_view& uniform_name, const float* data) const;

    Utils::Unique<ApiContext::ShaderDataApi> m_data;
};

}
