#include "Application/Application.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/Input.hpp"
#include "EntityManager.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Panels/Panels.hpp"
#include "Renderer/CamaraSystem.hpp"

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
    auto camara = Render::CamaraSystem::createCamera();
    EventDispatcher event_dispatcher;

    // unsigned int shader = Render::ShaderManager::createShader("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs.glsl");
    unsigned int model1 = Render::createModelEntity("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs.glsl");
    Render::loadDynamicModelFromFile(model1, "Hasbu/resources/Objects/backpack/backpack.obj");

    // unsigned int modelID = Render::createDynamicModel("Hasbu/resources/objects/backpack/backpack.obj");
    // unsigned int modelID = Render::createStaticModel("Hasbu/resources/objects/backpack/backpack.obj");

    // unsigned int shaderCube = Render::ShaderManager::createShader("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs2.glsl");
    unsigned int model2 = Render::createModelEntity("Hasbu/resources/Shaders/ModelLoading_vs.glsl", "Hasbu/resources/Shaders/ModelLoading_fs2.glsl");
    Render::loadStaticModelFromFile(model2, "Hasbu/resources/objects/rock/rock.obj");
    // unsigned int modeCube = Render::loadModel("Hasbu/resources/objects/rock/rock.obj");

    glm::vec3 ambientColor { 0.2f, 0.2f, 0.2f };
    glm::vec3 diffuseColor { 0.5f, 0.5f, 0.5f };
    glm::vec3 specularColor { 1.0f, 1.0f, 1.0f };
    glm::vec3 lightPosition(1.0f, 0.3f, 4.0f);

    auto& model1MatComponents = Render::getModelMaterialComponents(model1);
    auto& model2MatComponents = Render::getModelMaterialComponents(model2);

    while (m_window->shouldClose()) {
        auto& acitveCamaraComponents = Render::CamaraSystem::updateActiveCamara();
        double deltaTime = Render::RenderManager::getDeltaTime();

        Gui::ImGuiLayer::begin();
        Panels::debugPanel(glm::value_ptr(ambientColor), glm::value_ptr(diffuseColor), glm::value_ptr(specularColor), deltaTime);

        Render::RenderManager::clearWindow(0.1f, 0.1f, 0.1f, 1.0f);

        m_window->processInput();
        Render::CamaraSystem::processKeyBoardInputCamera(deltaTime);

        this->proccesInput();

        Render::ShaderManager::bind(model1MatComponents.shaderID);
        // Render::ShaderManager::setVec3(shader, "viewPosition", glm::value_ptr(Render::getCameraPosition(camera)));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "viewPosition", glm::value_ptr(acitveCamaraComponents.position));
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "material.shininess", 32.0f);

        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "dirLight.direction", glm::value_ptr(glm::vec3 { -0.2f, -1.0f, -0.3f }));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "dirLight.ambient", glm::value_ptr(glm::vec3 { 0.05f, 0.05f, 0.05f }));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "dirLight.diffuse", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "dirLight.specular", glm::value_ptr(glm::vec3 { 0.5f, 0.5f, 0.5f }));

        const auto pos = fmt::format("pointLights.position");
        const auto constant = fmt::format("pointLights.constant");
        const auto linear = fmt::format("pointLights.linear");
        const auto quadratic = fmt::format("pointLights.quadratic");
        const auto amb = fmt::format("pointLights.ambient");
        const auto diff = fmt::format("pointLights.diffuse");
        const auto spec = fmt::format("pointLights.specular");

        Render::ShaderManager::setVec3(model1MatComponents.shaderID, pos, glm::value_ptr(lightPosition));

        Render::ShaderManager::setVec3(model1MatComponents.shaderID, amb, glm::value_ptr(ambientColor));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, diff, glm::value_ptr(diffuseColor));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, spec, glm::value_ptr(specularColor));

        Render::ShaderManager::setFloat(model1MatComponents.shaderID, constant, 1.0f);
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, linear, 0.09f);
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, quadratic, 0.032f);
        // Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.position", glm::value_ptr(Render::getCameraPosition(camera)));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.position", glm::value_ptr(acitveCamaraComponents.position));
        // Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.direction", glm::value_ptr(Render::getCameraFront(camera)));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.direction", glm::value_ptr(acitveCamaraComponents.front));
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "spotLight.cutOff", cos(glm::radians(12.5f)));
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "spotLight.outerCutOff", cos(glm::radians(15.f)));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.ambient", glm::value_ptr(glm::vec3 { 0.0f, 0.0f, 0.0f }));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.diffuse", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setVec3(model1MatComponents.shaderID, "spotLight.specular", glm::value_ptr(glm::vec3 { 1.0f, 1.0f, 1.0f }));
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "spotLight.constant", 1.0f);
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "spotLight.linear", 0.9f);
        Render::ShaderManager::setFloat(model1MatComponents.shaderID, "spotLight.quadratic", 0.032f);

        // glm::mat4 projection = glm::perspective(glm::radians(Render::getCameraFov(camera)), m_window->getAspectRatio(), 0.1f, 100.0f);
        glm::mat4 projection = glm::perspective(glm::radians(acitveCamaraComponents.fov), m_window->getAspectRatio(), 0.1f, 100.0f);
        // glm::mat4 view = Render::getViewMatrix(camera);
        Render::ShaderManager::setM4f(model1MatComponents.shaderID, "projection", glm::value_ptr(projection));
        // Render::ShaderManager::setM4f(model1MatComponents.shaderID, "view", glm::value_ptr(view));
        Render::ShaderManager::setM4f(model1MatComponents.shaderID, "view", glm::value_ptr(acitveCamaraComponents.viewMatrix));

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        Render::ShaderManager::setM4f(model1MatComponents.shaderID, "model", glm::value_ptr(model));

        Render::ShaderManager::bind(model2MatComponents.shaderID);
        Render::ShaderManager::setM4f(model2MatComponents.shaderID, "projection", glm::value_ptr(projection));
        Render::ShaderManager::setM4f(model2MatComponents.shaderID, "view", glm::value_ptr(acitveCamaraComponents.viewMatrix));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        Render::ShaderManager::setM4f(model2MatComponents.shaderID, "model", glm::value_ptr(model));
        // Render::drawModel(modeCube, model2MatComponents.shaderID);

        EntityManager::drawEntities();
        Gui::ImGuiLayer::render();
        m_window->update();
    }
    Gui::ImGuiLayer::clear();
}

void Application::proccesInput()
{
    if (isKeyBeenPressed(KeyCode::ESCAPE)) {
        this->close();
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
