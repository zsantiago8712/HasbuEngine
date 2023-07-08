#pragma once
#include "Application/WindowData.hpp"
#include "Utilities/DynamicAllocator.hpp"

struct GLFWwindow;

namespace Hasbu::Core {

class Window {
public:
    explicit Window(const unsigned int width, const unsigned int height);
    explicit Window();

    void close();
    void clearWindow();
    void update();
    void processInput() const;
    bool shouldClose() const;

    constexpr float getAspectRatio() const
    {
        return static_cast<float>(m_data->m_width) / static_cast<float>(m_data->m_height);
    }

    constexpr float getWidth() const
    {
        return m_data->m_width;
    }


    constexpr float getHeight() const
    {
        return m_data->m_height;
    }


    Utils::Unique<WindowData> m_data = Utils::createUnique<WindowData>(nullptr);


};

double getTime();

}
