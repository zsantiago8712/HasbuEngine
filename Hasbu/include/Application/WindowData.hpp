#pragma once
#include "Utilities/DynamicAllocator.hpp"

namespace HasbuAPIContext {
struct Context;
}

namespace Hasbu {

struct WindowData {

    explicit WindowData(const unsigned int height, const unsigned int width);
    WindowData();
    ~WindowData();

    unsigned int width = 800;
    unsigned int height = 900;
    const std::string_view name = "Hasbu Engine";
    HasbuUtils::Unique<HasbuAPIContext::Context> context;
};

}
