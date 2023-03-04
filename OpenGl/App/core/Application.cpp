#include "Application.hpp"
#include "Glad/glad.h"
#include "Shader/ShaderManager.hpp"
#include "core/ElementBuffer.hpp"
#include "core/VertexArray.hpp"
#include "core/VertexBuffer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>

void framebuffer_size_callback(GLFWwindow* window [[maybe_unused]], int width, int height);

namespace hasbu {

void App::init()
{
    this->window.create();
    this->window.setFramebufferSizeCallback((void*)framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load GLAD\n";
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
#endif
}

void App::run(std::string_view const& vertex_shader_file, std::string_view const& fragment_shader_file)
{
    const float vertcices[] = {
        -0.5, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    const unsigned int indices[] = {
        0, 1, 3,
        0, 2, 3
    };

    Shader shader("triangle");

    shader.compile_shader("triangle", vertex_shader_file, TypeShader::VERTEX_SHADER);
    shader.compile_shader("triangle", fragment_shader_file, TypeShader::FRAGMENT_SHADER);

    shader.bind("triangle");

    VertexArray vao;
    VertexBuffer vbo(vertcices, sizeof(vertcices));
    ElementBuffer ebo(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    while (this->window.should_close() != WindowState::CLOSE) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind("triangle");
        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        this->window.process_input();

        this->window.swap_buffers();
        this->window.poll_events();
    }

    vbo.unbind();
}

}

void framebuffer_size_callback(GLFWwindow* window [[maybe_unused]], int width, int height)
{
    glViewport(0, 0, width, height);
}