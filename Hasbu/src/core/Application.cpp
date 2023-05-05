
#include "core/Application.hpp"
#include "Glad/glad.h"
#include "Render/GraphicContext.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexBufferLayout.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "Shader/ShaderManager.hpp"
#include "core/TextureManager.hpp"
#include "core/Window.hpp"
#include "defines.hpp"
#include <GLFW/glfw3.h>
#include <LA/la.hpp>
#include <cmath>
#include <cstddef>
#include <fmt/core.h>
#include <string>
#include <string_view>

namespace Hasbu {

void App::init()
{
    m_Window = createWindow(1200, 800, "Hasbu");
}

void App::run(std::string_view const& vertex_shader_file,
    std::string_view const& fragment_shader_file)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f
    };
    
    unsigned int indices[] = {
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

    Shader shader("triangle");
    shader.compile_shaders("triangle",
        vertex_shader_file, fragment_shader_file);
    shader.bind("triangle");

    Texture tex("Hasbu/resources/textures/container.jpg");
    Texture tex2("Hasbu/resources/textures/awesomeface.png");

    Shared<VertexArray> vao = createVertexArray();
    Shared<VertexBuffer> vbo = createVertexBuffer(vertices, sizeof(vertices));
    Shared<VertexBufferIndex> vbi = createVertexBufferIndex(indices,
        sizeof(indices));

    setVertexBufferIndex(vao, vbi);

    VertexBufferLayout vbl(
        {
            { BufferElementType::FLOAT_3, false },
            { BufferElementType::FLOAT_2, false },
        });

    setLayout(vbo, vbl);
    addVertexBuffer(vao, vbo);

    shader.bind("triangle");
    shader.setUniformI("triangle", "texture1", 0);
    shader.setUniformI("triangle", "texture2", 1);

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff = 0.0;
    unsigned int counter = 0;

    glEnable(GL_DEPTH_TEST);
    int i = 0;

    la::mat4 projection;
    projection = la::perspective(la::to_radians(45.0f),
        windowGetAspectRatio(m_Window), 0.1f, 100.0f);

    while (!windowShouldClose(m_Window)) {
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = FPS + "FPS / " + ms + " ms";
            windowSetTitle(m_Window, newTitle.data());
            prevTime = crntTime;
            counter = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        tex.activate(GL_TEXTURE0);
        tex2.activate(GL_TEXTURE1);

        shader.bind("triangle");

        shader.setUniformM4f("triangle", "projection",
            la::getPointer(projection));

        const float radius = 10.0f;
        const float camX = static_cast<float>(sin(glfwGetTime())) * radius;
        const float camZ = static_cast<float>(cos(glfwGetTime())) * radius;

        la::mat4 view;
        view = la::lookAt(la::vec3 { camX, 0.0f, camZ },
            la::vec3 { 0.0f, 0.0f, 0.0f }, la::vec3 { 0.0f, 1.0f, 0.0f });
        shader.setUniformM4f("triangle", "view", la::getPointer(view));

        bindVertexArray(vao);
        for (const auto& position : cubePositions) {
            float angle = 20.0f * i;
            la::mat4 model;
            
            model = la::translate(model, position);

            if (i % 3 == 0) {
                angle = 55.0 * crntTime;
            }
            model = la::rotate(model,
                la::vec3 { 1.0f, 0.3f, 0.5f }, la::to_radians(angle));

            shader.setUniformM4f("triangle", "model", la::getPointer(model));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
            i++;
        }

        i = 0;

        windowUpdate(m_Window);
    }
}

} // namespace Hasbu
