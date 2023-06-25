#include "Application.hpp"

int main()
{

    Hasbu::Core::Application& app = Hasbu::Core::Application::createApplication();

    app.start();

    app.run();

    return 0;
}
