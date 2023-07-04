#include "Application/Application.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/Input.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Panels/Panels.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/ModelsManager.hpp"
#include "Renderer/RenderManager.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Utilities/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hasbu::Core {

Application& Application::getInstace()
{
    static Application instance;
    return instance;
}

void* Application::getNativeWindow()
{
    return getInstace().m_window->m_data->m_window;
}

Application& Application::createApplication(void)
{
    Utils::Logger::initLogger();
    Utils::DynamicAllocator::initDynamicAllocator(TO_GYGABYTES(1));
    Utils::DynamicAllocator::getReport();

    HASBU_INFO("Application created correctly");
    Utils::DynamicAllocator::getReport();

    return Application::getInstace();
}

void Application::start()
{
    HASBU_INFO("Application started");
    Render::RenderManager::createRenderContext();
}

void Application::run()
{
    Gui::ImGuiLayer::create();
    Render::Camera camera;
    EventDispatcher event_dispatcher(camera);

    unsigned int shader = Render::ShaderManager::createShader("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs.glsl");
    unsigned int modelID = Render::loadModel("Hasbu/resources/objects/backpack/backpack.obj");

    unsigned int shaderCube = Render::ShaderManager::createShader("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs2.glsl");
    unsigned int modeCube = Render::loadModel("Hasbu/resources/objects/rock/rock.obj");

    glm::vec3 ambientColor { 0.2f, 0.2f, 0.2f };
    glm::vec3 diffuseColor { 0.5f, 0.5f, 0.5f };
    glm::vec3 specularColor { 1.0f, 1.0f, 1.0f };
    glm::vec3 lightPosition(1.0f, 0.3f, 4.0f);

    while (m_window->shouldClose()) {

        double deltaTime = Render::RenderManager::getDeltaTime();
        Gui::ImGuiLayer::begin();
        Panels::debugPanel(glm::value_ptr(ambientColor), glm::value_ptr(diffuseColor), glm::value_ptr(specularColor), deltaTime);

        Render::RenderManager::clearWindow(0.1f, 0.1f, 0.1f, 1.0f);

        m_window->processInput();
        camera.proccesKeyBoard(deltaTime);
        this->proccesInput();

        Render::ShaderManager::bind(shader);
        Render::ShaderManager::setVec3(shader, "viewPosition", glm::value_ptr(camera.m_position));
        Render::ShaderManager::setFloat(shader, "material.shininess", 32.0f);

        Render::ShaderManager::setVec3(shader, "dirLight.direction", glm::value_ptr(glm::vec3 { -0.2f, -1.0f, -0.3f }));
        Render::ShaderManager::setVec3(shader, "dirLight.ambient", glm::value_ptr(glm::vec3 { 0.05f, 0.05f, 0.05f }));
        Render::ShaderManager::setVec3(shader, "dirLight.diffuse", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setVec3(shader, "dirLight.specular", glm::value_ptr(glm::vec3 { 0.5f, 0.5f, 0.5f }));

        const auto pos = fmt::format("pointLights.position");
        const auto constant = fmt::format("pointLights.constant");
        const auto linear = fmt::format("pointLights.linear");
        const auto quadratic = fmt::format("pointLights.quadratic");
        const auto amb = fmt::format("pointLights.ambient");
        const auto diff = fmt::format("pointLights.diffuse");
        const auto spec = fmt::format("pointLights.specular");

        Render::ShaderManager::setVec3(shader, pos, glm::value_ptr(lightPosition));

        Render::ShaderManager::setVec3(shader, amb, glm::value_ptr(ambientColor));
        Render::ShaderManager::setVec3(shader, diff, glm::value_ptr(diffuseColor));
        Render::ShaderManager::setVec3(shader, spec, glm::value_ptr(specularColor));

        Render::ShaderManager::setFloat(shader, constant, 1.0f);
        Render::ShaderManager::setFloat(shader, linear, 0.09f);
        Render::ShaderManager::setFloat(shader, quadratic, 0.032f);
        Render::ShaderManager::setVec3(shader, "spotLight.position", glm::value_ptr(camera.m_position));
        Render::ShaderManager::setVec3(shader, "spotLight.direction", glm::value_ptr(camera.m_front));
        Render::ShaderManager::setFloat(shader, "spotLight.cutOff", cos(glm::radians(12.5f)));
        Render::ShaderManager::setFloat(shader, "spotLight.outerCutOff", cos(glm::radians(15.f)));
        Render::ShaderManager::setVec3(shader, "spotLight.ambient", glm::value_ptr(glm::vec3 { 0.0f, 0.0f, 0.0f }));
        Render::ShaderManager::setVec3(shader, "spotLight.diffuse", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setVec3(shader, "spotLight.specular", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setFloat(shader, "spotLight.constant", 1.0f);
        Render::ShaderManager::setFloat(shader, "spotLight.linear", 0.9f);
        Render::ShaderManager::setFloat(shader, "spotLight.quadratic", 0.032f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.m_fov), m_window->getAspectRatio(), 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        Render::ShaderManager::setM4f(shader, "projection", glm::value_ptr(projection));
        Render::ShaderManager::setM4f(shader, "view", glm::value_ptr(view));

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        Render::ShaderManager::setM4f(shader, "model", glm::value_ptr(model));

        Render::drawModel(modelID, shader);

        Render::ShaderManager::bind(shaderCube);
        Render::ShaderManager::setM4f(shaderCube, "projection", glm::value_ptr(projection));
        Render::ShaderManager::setM4f(shaderCube, "view", glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        Render::ShaderManager::setM4f(shaderCube, "model", glm::value_ptr(model));
        Render::drawModel(modeCube, shaderCube);

        Gui::ImGuiLayer::render();
        m_window->update();
    }

    Gui::ImGuiLayer::clear();
}

void Application::proccesInput()
{
    if (isKeyBeenPressed(KeyCode::ESCAPE)) {
        this->close();
    } else if (isKeyBeenPressed(KeyCode::R)) {
        Render::ShaderManager::reaload();
    }
}

void Application::close()
{
    HASBU_INFO("CLOSING Application");
    this->m_window->close();
}

Application::~Application()
{
    this->m_window.reset();
    Utils::DynamicAllocator::getReport();
}
}
