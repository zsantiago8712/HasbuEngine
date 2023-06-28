#include "Application/Application.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/Input.hpp"
#include "Imgui/ImguiLayer.hpp"
#include "KeyCodes.hpp"
#include "Panels/Panels.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Render.hpp"
#include "Renderer/RenderManager.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
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

    Gui::ImGuiLayer::create();

    Render::Camera camera;
    EventDispatcher event_dispatcher(camera);

    Render::Shader ligthingShader;
    ligthingShader.create("Hasbu/resources/Shaders/Colors_vs.glsl", "Hasbu/resources/Shaders/Colors_fs.glsl");

    Render::Shader lightsCubeShader;
    lightsCubeShader.create("Hasbu/resources/Shaders/Ligths_vs.glsl", "Hasbu/resources/Shaders/Ligths_fs.glsl");

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

    // Render::Texture texture1;
    // texture1.create("Hasbu/resources/Textures/container.jpg");

    // Render::Texture texture2;
    // texture2.create("Hasbu/resources/Textures/awesomeface.png");

    glm::vec3 ligttPos(1.2f, 1.0f, 2.0f);

    glm::vec3 colorCube(1.0f, 0.5, .3f);
    glm::vec3 lights(1.0f, 1.0f, 1.0f);

    float ambientStrength = 0.1f;
    int iluminationSelected = 0;
    float specularStrength = 0.5f;

    // shader.setInt("texture1", 0);
    // shader.setInt("texture2", 1);

    // Render::Mesh mesh;

    while (m_window->shouldClose()) {

        double deltaTime = Render::Renderer::getDeltaTime();
        Gui::ImGuiLayer::begin();
        Panels::debugPanel(&colorCube[0], deltaTime, ambientStrength, specularStrength, iluminationSelected);

        Render::Renderer::clearWindow(0.0f, 0.0f, 0.0f);

        m_window->processInput();
        camera.proccesKeyBoard(deltaTime);
        this->proccesInput();

        // texture1.bind(1);
        // texture2.bind(2);

        glm::vec3 newColor { sin(getTime()) * 0.5f, cos(getTime()) * 0.5f, cos(getTime()) * sin(getTime()) };

        glm::vec3 newPosition { static_cast<float>(cos(getTime())), 0.3f, static_cast<float>(sin(getTime())) };
        glm::vec3 newPosition2 = { 0.5, static_cast<float>(sin(getTime())), static_cast<float>(cos(getTime())) };

        ligthingShader.bind();
        ligthingShader.setInt("selectLighting", iluminationSelected);
        ligthingShader.setVec3("objectColor", glm::value_ptr(colorCube));
        // ligthingShader.setVec3("lightColor", glm::value_ptr(lights));
        ligthingShader.setVec3("lightColor", glm::value_ptr(newColor));
        // ligthingShader.setVec3("lightPosition", glm::value_ptr(ligttPos));

        ligthingShader.setVec3("lightPosition", glm::value_ptr(newPosition));
        ligthingShader.setVec3("lightPosition2", glm::value_ptr(newPosition2));

        ligthingShader.setVec3("viewPosition", glm::value_ptr(camera.m_position));
        ligthingShader.setFloat("ambientStrength", ambientStrength);
        ligthingShader.setFloat("specularStrength", specularStrength);

        glm::mat4 projection = glm::perspective(glm::radians(camera.m_fov),
            m_window->getAspectRatio(), 0.1f, 100.0f);
        ligthingShader.setM4f("projection", glm::value_ptr(projection));

        glm::mat4 view = camera.getViewMatrix();
        ligthingShader.setM4f("view", glm::value_ptr(view));

        auto model = glm::mat4(1.0f);
        float angle = getTime() * 55.0f;
        model = glm::rotate(model, glm::radians(angle), { 0.0, 1.0f, 0.0f });
        ligthingShader.setM4f("model", glm::value_ptr(model));

        Render::RenderManager::bindVAO(cube_vao);
        Render::Renderer::drawElements(_indices.size());

        lightsCubeShader.bind();
        lightsCubeShader.setM4f("projection", glm::value_ptr(projection));
        lightsCubeShader.setM4f("view", glm::value_ptr(view));

        lightsCubeShader.setVec3("color", glm::value_ptr(newColor));

        model = glm::mat4(1.0f);

        model = glm::translate(model, newPosition);

        // model = glm::translate(model, ligttPos);
        model
            = glm::scale(model, glm::vec3(0.2f));
        lightsCubeShader.setM4f("model", glm::value_ptr(model));

        Render::RenderManager::bindVAO(lightCube_vao);
        Render::Renderer::drawElements(_indices.size());

        glm::vec3 newColor2 { cos(getTime()) * 2.5f, cos(getTime()) * 2.5f, cos(getTime()) * sin(getTime()) };

        lightsCubeShader.setVec3("color", glm::value_ptr(newColor2));

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPosition2);

        // model = glm::translate(model, ligttPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightsCubeShader.setM4f("model", glm::value_ptr(model));

        Render::Renderer::drawElements(_indices.size());

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
