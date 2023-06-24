#include "Application.hpp"

int main()
{

    Hasbu::Application& app = Hasbu::Application::createApplication();

    app.start();

    app.run();

    return 0;
}
