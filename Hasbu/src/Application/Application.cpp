#include "Application/Application.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/Input.hpp"
#include "ImGuiLayer/ImguiLayer.hpp"
#include "Panels/Panels.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/RenderManager.hpp"
#include "Renderer/ShaderManager.hpp"
#include "Renderer/TextureManager.hpp"
#include "Utilities/Logger.hpp"
#include <array>
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

    std::array<Render::Vertex, 24> _vertices {
        // Front Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_normal { 0.0f, 0.0f, -1.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_normal { 0.0f, 0.0f, -1.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_normal { 0.0f, 0.0f, -1.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_normal { 0.0f, 0.0f, -1.0f }, .m_textCoords { 0.0f, 1.0f } },

        // Back Face
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_normal { 0.0f, 0.0f, 1.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_normal { 0.0f, 0.0f, 1.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_normal { 0.0f, 0.0f, 1.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_normal { 0.0f, 0.0f, 1.0f }, .m_textCoords { 0.0f, 1.0f } },

        // Top Face
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_normal { 0.0f, 1.0f, 0.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_normal { 0.0f, 1.0f, 0.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_normal { 0.0f, 1.0f, 0.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_normal { 0.0f, 1.0f, 0.0f }, .m_textCoords { 0.0f, 1.0f } },

        // Bottom Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_normal { 0.0f, -1.0f, 0.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_normal { 0.0f, -1.0f, 0.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_normal { 0.0f, -1.0f, 0.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_normal { 0.0f, -1.0f, 0.0f }, .m_textCoords { 0.0f, 1.0f } },

        // Left Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_normal { -1.0f, 0.0f, 0.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_normal { -1.0f, 0.0f, 0.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_normal { -1.0f, 0.0f, 0.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_normal { -1.0f, 0.0f, 0.0f }, .m_textCoords { 0.0f, 1.0f } },

        // Right Face
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_normal { 1.0f, 0.0f, 0.0f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_normal { 1.0f, 0.0f, 0.0f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_normal { 1.0f, 0.0f, 0.0f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_normal { 1.0f, 0.0f, 0.0f }, .m_textCoords { 0.0f, 1.0f } }
    };

    std::array<unsigned int, 36> _indices {
        0, 1, 3,
        1, 2, 3,

        4, 5, 7,
        5, 6, 7,

        8, 9, 11,
        9, 10, 11,

        12, 13, 15,
        13, 14, 15,

        16, 17, 19,
        17, 18, 19,

        20, 21, 23,
        21, 22, 23
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };

    Gui::ImGuiLayer::create();

    Render::Camera camera;
    EventDispatcher event_dispatcher(camera);

    unsigned int ligthingShader = Render::ShaderManager::createShader("Hasbu/resources/Shaders/MultipleLights_vs.glsl", "Hasbu/resources/Shaders/MultipleLights_fs.glsl");

    unsigned int lightsCubeShader = Render::ShaderManager::createShader("Hasbu/resources/Shaders/Ligths_vs.glsl", "Hasbu/resources/Shaders/Ligths_fs.glsl");

    unsigned int cube_vao = Render::RenderManager::createVAO();
    unsigned int vbo = Render::RenderManager::createVBO(_vertices);
    unsigned int ebo = Render::RenderManager::createEBO(_indices);
    Render::RenderManager::attribPointer(Render::VertexAttrib::POSITIONS);
    Render::RenderManager::attribPointer(Render::VertexAttrib::NORMALS);
    Render::RenderManager::attribPointer(Render::VertexAttrib::TEXTURES_COORDS);

    unsigned int lightCube_vao = Render::RenderManager::createVAO();
    Render::RenderManager::bindVBO(vbo);
    unsigned int lightCube_ebo = Render::RenderManager::createEBO(_indices);
    Render::RenderManager::attribPointer(Render::VertexAttrib::POSITIONS);
    Render::RenderManager::attribPointer(Render::VertexAttrib::NORMALS);
    Render::RenderManager::attribPointer(Render::VertexAttrib::TEXTURES_COORDS);

    auto texture1 = Render::TextureManager::createTexture("Hasbu/resources/Textures/container2.png");
    auto texture2 = Render::TextureManager::createTexture("Hasbu/resources/Textures/container2_specular.png");
    auto texture3 = Render::TextureManager::createTexture("Hasbu/resources/Textures/matrix.jpg");

    // glm::vec3 ligttPos(1.2f, 1.0f, 2.0f);
    glm::vec3 ligttPos(-0.2f, -1.0f, -0.3f);

    glm::vec3 ambientColor { 0.2f, 0.2f, 0.2f };
    glm::vec3 diffuseColor { 0.5f, 0.5f, 0.5f };
    glm::vec3 specularColor { 1.0f, 1.0f, 1.0f };

    // Render::Mesh mesh;
    Render::ShaderManager::bind(ligthingShader);
    Render::ShaderManager::setInt(ligthingShader, "material.diffuse", 0);
    Render::ShaderManager::setInt(ligthingShader, "material.specular", 1);
    Render::ShaderManager::setInt(ligthingShader, "material.emission", 2);

    while (m_window->shouldClose()) {

        double deltaTime = Render::RenderManager::getDeltaTime();
        Gui::ImGuiLayer::begin();
        Panels::debugPanel(glm::value_ptr(ambientColor), glm::value_ptr(diffuseColor), glm::value_ptr(specularColor), deltaTime);

        ligttPos = { 0.25f, cos(getTime()) * 1.5f, sin(getTime()) * 2.0f };
        Render::RenderManager::clearWindow(0.1f, 0.1f, 0.1f, 1.0f);

        m_window->processInput();
        camera.proccesKeyBoard(deltaTime);
        this->proccesInput();

        Render::ShaderManager::bind(ligthingShader);

        Render::ShaderManager::setVec3(ligthingShader, "viewPosition", glm::value_ptr(camera.m_position));
        Render::ShaderManager::setFloat(ligthingShader, "material.shininess", 32.0f);

        Render::ShaderManager::setVec3(ligthingShader, "dirLight.direction", glm::value_ptr(glm::vec3 { -0.2f, -1.0f, -0.3f }));
        Render::ShaderManager::setVec3(ligthingShader, "dirLight.ambient", glm::value_ptr(glm::vec3 { 0.05f, 0.05f, 0.05f }));
        Render::ShaderManager::setVec3(ligthingShader, "dirLight.diffuse", glm::value_ptr(glm::vec3 { 0.4f, 0.4f, 0.4f }));
        Render::ShaderManager::setVec3(ligthingShader, "dirLight.specular", glm::value_ptr(glm::vec3 { 0.5f, 0.5f, 0.5f }));

        for (int i = 0; i < 4; i++) {
            pointLightPositions[i] = { cos(getTime()) * 2.3 + i, sin(getTime()) * 3.8 + i, (sin(getTime()) * cos(getTime())) * 1.2 + i};
            const auto pos = fmt::format("pointLights[{}].position", i);
            const auto constant = fmt::format("pointLights[{}].constant", i);
            const auto linear = fmt::format("pointLights[{}].linear", i);
            const auto quadratic = fmt::format("pointLights[{}].quadratic", i);
            const auto amb = fmt::format("pointLights[{}].ambient", i);
            const auto diff = fmt::format("pointLights[{}].diffuse", i);
            const auto spec = fmt::format("pointLights[{}].specular", i);

            Render::ShaderManager::setVec3(ligthingShader, pos, glm::value_ptr(pointLightPositions[i]));

            Render::ShaderManager::setVec3(ligthingShader, amb, glm::value_ptr(ambientColor));
            Render::ShaderManager::setVec3(ligthingShader, diff, glm::value_ptr(diffuseColor));
            Render::ShaderManager::setVec3(ligthingShader, spec, glm::value_ptr(specularColor));

            Render::ShaderManager::setFloat(ligthingShader, constant, 1.0f);
            Render::ShaderManager::setFloat(ligthingShader, linear, 0.09f);
            Render::ShaderManager::setFloat(ligthingShader, quadratic, 0.032f);
        }

        Render::ShaderManager::setVec3(ligthingShader, "spotLight.position", glm::value_ptr(camera.m_position));
        Render::ShaderManager::setVec3(ligthingShader, "spotLight.direction", glm::value_ptr(camera.m_front));
        Render::ShaderManager::setFloat(ligthingShader, "spotLight.cutOff", cos(glm::radians(12.5f)));
        Render::ShaderManager::setFloat(ligthingShader, "spotLight.outerCutOff", cos(glm::radians(15.f)));
        Render::ShaderManager::setVec3(ligthingShader, "spotLight.ambient", glm::value_ptr(glm::vec3 {0.0f, 0.0f, 0.0f}));
        Render::ShaderManager::setVec3(ligthingShader, "spotLight.diffuse", glm::value_ptr(glm::vec3 {1.0f, 1.0f, 1.0f}));
        Render::ShaderManager::setVec3(ligthingShader, "spotLight.specular", glm::value_ptr(glm::vec3 {1.0f, 1.0f, 1.0f}));
        Render::ShaderManager::setFloat(ligthingShader, "spotLight.constant", 1.0f);
        Render::ShaderManager::setFloat(ligthingShader, "spotLight.linear", 0.9f);
        Render::ShaderManager::setFloat(ligthingShader, "spotLight.quadratic", 0.032f);
        

        Render::TextureManager::activate(texture1, 1);
        Render::TextureManager::activate(texture2, 2);
        Render::TextureManager::activate(texture3, 3);
        Render::RenderManager::bindVAO(cube_vao);

        glm::mat4 projection = glm::perspective(glm::radians(camera.m_fov),
            m_window->getAspectRatio(), 0.1f, 100.0f);
        Render::ShaderManager::setM4f(ligthingShader, "projection", glm::value_ptr(projection));

        glm::mat4 view = camera.getViewMatrix();
        Render::ShaderManager::setM4f(ligthingShader, "view", glm::value_ptr(view));

        auto model = glm::mat4(1.0f);

        int i = 0;
        for (const auto postion : cubePositions) {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(i * 20.0f), { 1.0f, 0.3, 0.5f });
            model = glm::translate(model, postion);
            Render::ShaderManager::setM4f(ligthingShader, "model", glm::value_ptr(model));

            Render::RenderManager::drawElements(_indices.size());
            i++;
        }

        Render::ShaderManager::bind(lightsCubeShader);
        Render::ShaderManager::setM4f(lightsCubeShader, "projection", glm::value_ptr(projection));
        Render::ShaderManager::setM4f(lightsCubeShader, "view", glm::value_ptr(view));

        
        Render::RenderManager::bindVAO(lightCube_vao);

        for(unsigned int i = 0; i < 4; i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            model = glm::rotate(model, (float)glm::radians(deltaTime * 44.2f), { 1.0f, 0.3f, 0.5f });

            Render::ShaderManager::setM4f(lightsCubeShader, "model", glm::value_ptr(model));
            Render::ShaderManager::setVec3(lightsCubeShader, "color", glm::value_ptr(diffuseColor));

            Render::RenderManager::drawElements(_indices.size());
        }
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
