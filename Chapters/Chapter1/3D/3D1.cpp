
#include "Glad/glad.h"
#include "Render/GraphicContext.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexBufferLayout.hpp"
#include "Render/VertexIndexBuffer.hpp"
#include "Shader/ShaderManager.hpp"
#include "core/Application.hpp"
#include "core/TextureManager.hpp"
#include "core/Window.hpp"
#include "defines.hpp"
#include "details/_common.hpp"
#include "details/_mat4_f.hpp"
#include "details/_mat_transform.hpp"
#include "details/_pointer_type.hpp"
#include <GLFW/glfw3.h>
#include <LA/la.hpp>
#include <cmath>
#include <fmt/core.h>
#include <string>
#include <string_view>

namespace Hasbu {

void App::init()
{
    m_Window = createWindow(800, 600, "Hasbu");
}

void App::run(std::string_view const& vertex_shader_file, std::string_view const& fragment_shader_file)
{
    float vertices[] = {
        // positions                            // colors                           // texture coords
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f // bottom right
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    Shader shader("triangle");
    shader.compile_shaders("triangle", vertex_shader_file, fragment_shader_file);
    shader.bind("triangle");

    Texture tex("/Users/randymarsh/Developer/OpenGL/Hasbu/resources/textures/container.jpg");
    Texture tex2("/Users/randymarsh/Developer/OpenGL/Hasbu/resources/textures/awesomeface.png");

    Shared<VertexArray> vao = createVertexArray();
    Shared<VertexBuffer> vbo = createVertexBuffer(vertices, sizeof(vertices));
    Shared<VertexBufferIndex> vbi = createVertexBufferIndex(indices, sizeof(indices));
    setVertexBufferIndex(vao, vbi);

    VertexBufferLayout vbl(
        { { BufferElementType::FLOAT_3, false },
            { BufferElementType::FLOAT_3, false },
            { BufferElementType::FLOAT_2, false } });
    setLayout(vbo, vbl);

    addVertexBuffer(vao, vbo);

    shader.bind("triangle");
    shader.setUniformI("triangle", "texture1", 0);
    shader.setUniformI("triangle", "texture2", 1);

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff = 0.0;
    unsigned int counter = 0;

    la::mat4 model;
    model = la::rotate(model, la::vec3 { 1.0f, 0.0f, 0.0f }, la::to_radians(-55.0f));

    la::mat4 view;
    view = la::translate(view, la::vec3 { 0.0f, 0.0f, -3.0 });

    la::mat4 projection;
    projection = la::perspective(la::to_radians(45.0f), windowGetAspectRatio(m_Window), 0.1f, 100.0f);

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

        projection = la::perspective(la::to_radians(45.0f), windowGetAspectRatio(m_Window), 0.1f, 100.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        tex.activate(GL_TEXTURE0);
        tex2.activate(GL_TEXTURE1);

        shader.bind("triangle");
        shader.setUniformM4f("triangle", "model", la::getPointer(model));
        shader.setUniformM4f("triangle", "view", la::getPointer(view));
        shader.setUniformM4f("triangle", "projection", la::getPointer(projection));
        bindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        windowPollEvents(m_Window);
        windowUpdate(m_Window);
    }
}

}
