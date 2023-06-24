#include "Application/Application.hpp"
// #include "LA/la.hpp"
// #include "Mesh.hpp"
// #include "OpenGL/VertexArray.hpp"
#include "API/VertexArray.hpp"
#include "Application/Input.hpp"
#include "EventDispatcher.hpp"
#include "KeyCodes.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Context.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>

namespace Hasbu {

Application& Application::getInstace()
{
    static Application instance;
    return instance;
}

void* Application::getNativeWindow()
{
    return getInstace().window->native_window;
}

Application& Application::createApplication(void)
{
    HasbuUtils::Logger::initLogger();
    HasbuUtils::DynamicAllocator::initDynamicAllocator(TO_GYGABYTES(1));
    HasbuUtils::DynamicAllocator::getReport();

    HASBU_INFO("Application created correctly");
    HasbuUtils::DynamicAllocator::getReport();

    return Application::getInstace();
}

void Application::start()
{
    HASBU_INFO("Application started");
}

void Application::run()
{

    HasbuRender::Camera camera;
    Hasbu::EventDispatcher event_dispatcher(camera);

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

    std::array<HasbuRender::Vertex, 24> _vertices {
        // Front Face
        HasbuRender::Vertex { .position { -0.5f, -0.5f, -0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, -0.5f, -0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, -0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { -0.5f, 0.5f, -0.5f }, .text_coords { 0.0f, 1.0f } },

        // Back Face
        HasbuRender::Vertex { .position { -0.5f, -0.5f, 0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, -0.5f, 0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, 0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { -0.5f, 0.5f, 0.5f }, .text_coords { 0.0f, 1.0f } },

        // Top Face
        HasbuRender::Vertex { .position { -0.5f, 0.5f, -0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, -0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, 0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { -0.5f, 0.5f, 0.5f }, .text_coords { 0.0f, 1.0f } },

        // Bottom Face
        HasbuRender::Vertex { .position { -0.5f, -0.5f, -0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, -0.5f, -0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, -0.5f, 0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { -0.5f, -0.5f, 0.5f }, .text_coords { 0.0f, 1.0f } },

        // Left Face
        HasbuRender::Vertex { .position { -0.5f, -0.5f, -0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { -0.5f, -0.5f, 0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { -0.5f, 0.5f, 0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { -0.5f, 0.5f, -0.5f }, .text_coords { 0.0f, 1.0f } },

        // Right Face
        HasbuRender::Vertex { .position { 0.5f, -0.5f, -0.5f }, .text_coords { 0.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, -0.5f, 0.5f }, .text_coords { 1.0f, 0.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, 0.5f }, .text_coords { 1.0f, 1.0f } },
        HasbuRender::Vertex { .position { 0.5f, 0.5f, -0.5f }, .text_coords { 0.0f, 1.0f } }
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
    HasbuRender::Shader shader;
    shader.create("Hasbu/resources/Shaders/3D.vs", "Hasbu/resources/Shaders/3D.fs");

    HasbuAPIContext::VertexArray vertexArray;
    vertexArray.create(_vertices, _indices);

    vertexArray.attribPointer(HasbuAPIContext::VertexAttrib::POSITIONS);
    vertexArray.attribPointer(HasbuAPIContext::VertexAttrib::TEXTURES_COORDS);

    HasbuRender::Texture texture1;
    texture1.create("Hasbu/resources/Textures/container.jpg");

    HasbuRender::Texture texture2;
    texture2.create("Hasbu/resources/Textures/awesomeface.png");

    shader.bind();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // HasbuRender::Mesh mesh;

    la::mat4 projection;
    projection = la::perspective(la::to_radians(45.0f),
        getAspectRatio(this->window->data), 1.0f, 100.0f);

    shader.setM4f("projection", la::getPointer(projection));

    int i = 0;

    while (shouldClose(this->window->native_window)) {

        HasbuRender::clearWindow();
        // camera.proccesKeyBoard();
        processInput();

        texture1.bind(1);
        texture2.bind(2);

        shader.bind();
        //     mesh.setupDraw(shader);

        double crnt_time = getTime();

        la::mat4 view = camera.getViewMatrix();

        shader.setM4f("view", la::getPointer(view));

        vertexArray.bind();
        for (const auto& position : cubePositions) {
            float angle = 20.0f * i;
            la::mat4 model;

            model = la::translate(model, position);

            if (i % 3 == 0) {
                angle = 55.0 * crnt_time;
            }
            model = la::rotate(model,
                la::vec3 { 100.0f, 0.0f, 0.0f }, la::to_radians(angle));

            shader.setM4f("model", la::getPointer(model));

            glDrawElements(GL_TRIANGLES, static_cast<int>(_indices.size()), GL_UNSIGNED_INT, nullptr);
            // mesh.draw();
            i++;
        }

        i = 0;
        windowUpdate(this->window->native_window);
    }
}

void Application::proccesInput()
{
    if (isKeyBeenRelased(Hasbu::KeyCode::ESCAPE)) {
        this->close();
    }
}

void Application::close()
{
    HASBU_INFO("CLOSING Application");
    this->window->close();
}

Application::~Application()
{
    this->window.reset();
    HasbuUtils::DynamicAllocator::getReport();
}
}
