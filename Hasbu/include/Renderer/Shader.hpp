#pragma once

#include "Utilities/DynamicAllocator.hpp"
#include <string_view>

namespace HasbuAPIContext {
struct ShaderDataApi;
}

namespace HasbuRender {

struct Shader {

    Shader();
    ~Shader();

    void create(const std::string_view& vs_file, const std::string_view& fs_file);
    void bind() const;
    void unBind() const;

    HasbuUtils::Shared<HasbuAPIContext::ShaderDataApi> data;

    void setInt(const std::string_view& uniform_name, const int& data);
    void setM4f(const std::string_view& uniform_name, const float* data);
};

}
