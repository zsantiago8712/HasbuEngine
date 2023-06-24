#pragma once
#include "Utilities/DynamicAllocator.hpp"
#include "Window.hpp"

namespace Hasbu {

class Application {
public:
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    static Application& createApplication(void);
    static Application& getInstace();
    static void* getNativeWindow();

    void proccesInput();

    void start();
    void run();
    void close();

private:
    Application() = default;
    ~Application();
    HasbuUtils::Unique<Window> window = HasbuUtils::createUnique<Window>();
};

}
