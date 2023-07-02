#pragma once
#include "Application/Window.hpp"
namespace Hasbu::Core {

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
    Utils::Unique<Window> m_window = Utils::createUnique<Window>();
};

}
