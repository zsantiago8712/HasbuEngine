#include "Application/Application.hpp"
#include "API/VertexArray.hpp"
#include "Application/EventDispatcher.hpp"
#include "Application/Input.hpp"

#include "KeyCodes.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Render.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

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

    Render::Camera camera;
    EventDispatcher event_dispatcher(camera);

    la::vec3 cubePositions[] = {
        la::vec3(0.0f, 0.0f, 0.0f),
        la::vec3(2.0f, 5.0f, -15.0f),
        la::vec3(-1.5f, -2.2f, -2.5f),
        la::vec3(-3.8f, -2.0f, -12.3f),
        la::vec3(2.4f, -0.4f, -3.5f),
        la::vec3(-1.7f, 3.0f, -7.5f),
        la::vec3(1.3f, -2.0f, -2.5f),
        la::vec3(1.5f, 2.0f, -2.5f),
        la::vec3(1.5f, 0.2f, -1.5f),
        la::vec3(-1.3f, 1.0f, -1.5f)
    };

    std::array<Render::Vertex, 24> _vertices {
        // Front Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_textCoords { 0.0f, 1.0f } },

        // Back Face
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_textCoords { 0.0f, 1.0f } },

        // Top Face
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_textCoords { 0.0f, 1.0f } },

        // Bottom Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_textCoords { 0.0f, 1.0f } },

        // Left Face
        Render::Vertex { .m_position { -0.5f, -0.5f, -0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { -0.5f, -0.5f, 0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, 0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { -0.5f, 0.5f, -0.5f }, .m_textCoords { 0.0f, 1.0f } },

        // Right Face
        Render::Vertex { .m_position { 0.5f, -0.5f, -0.5f }, .m_textCoords { 0.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, -0.5f, 0.5f }, .m_textCoords { 1.0f, 0.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, 0.5f }, .m_textCoords { 1.0f, 1.0f } },
        Render::Vertex { .m_position { 0.5f, 0.5f, -0.5f }, .m_textCoords { 0.0f, 1.0f } }
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
    Render::Shader shader;
    shader.create("Hasbu/resources/Shaders/3D.vs", "Hasbu/resources/Shaders/3D.fs");

    Render::VertexArray vertexArray;
    vertexArray.create(_vertices, _indices);

    vertexArray.attribPointer(Render::VertexAttrib::POSITIONS);
    vertexArray.attribPointer(Render::VertexAttrib::TEXTURES_COORDS);

    Render::Texture texture1;
    texture1.create("Hasbu/resources/Textures/container.jpg");

    Render::Texture texture2;
    texture2.create("Hasbu/resources/Textures/awesomeface.png");

    shader.bind();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // Render::Mesh mesh;

    la::mat4 projection;
    projection = la::perspective(la::to_radians(45.0f),
        m_window->getAspectRatio(), 1.0f, 100.0f);

    shader.setM4f("projection", la::getPointer(projection));

    int i = 0;

    while (m_window->shouldClose()) {

        double delta = Render::Renderer::getDeltaTime();
        Render::Renderer::clearWindow();

        m_window->processInput(delta);
        camera.proccesKeyBoard(delta);
        this->proccesInput();

        texture1.bind(1);
        texture2.bind(2);

        shader.bind();

        double currentTime = getTime();

        la::mat4 view = camera.getViewMatrix();

        shader.setM4f("view", la::getPointer(view));

        vertexArray.bind();
        for (const auto& position : cubePositions) {
            float angle = 20.0f * i;
            la::mat4 model;

            model = la::translate(model, position);

            // if (i % 3 == 0) {
            //     angle = 55.0 * currentTime;
            // }
            // model = la::rotate(model,
            //     la::vec3 { 100.0f, 0.0f, 0.0f }, la::to_radians(angle));

            shader.setM4f("model", la::getPointer(model));

            glDrawElements(GL_TRIANGLES, static_cast<int>(_indices.size()), GL_UNSIGNED_INT, nullptr);
            i++;
        }

        i = 0;
        m_window->update();
    }
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
