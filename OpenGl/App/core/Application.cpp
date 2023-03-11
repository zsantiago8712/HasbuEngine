#include "Application.hpp"
#include "Glad/glad.h"
#include <Shader/ShaderManager.hpp>
#include <cmath>
#include <core/ElementBuffer.hpp>
#include <core/TextureManager.hpp>
#include <core/VertexArray.hpp>
#include <core/VertexBuffer.hpp>
#include <core/VertexBufferLayout.hpp>

#include <GLFW/glfw3.h>
#include <LA/la.hpp>
#include <fmt/core.h>
#include <string_view>

void framebuffer_size_callback(GLFWwindow* window [[maybe_unused]], int width, int height);

namespace hasbu {

void App::init()
{
    this->window.create();
    this->window.setFramebufferSizeCallback((void*)framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::print(stderr, "Failed to load GLAD\n");
        exit(EXIT_FAILURE);
    }

    int nrAttrubutes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrubutes);
    fmt::print("Maximum nr of vertex attributes supported: {}\n", nrAttrubutes);
}

void App::run(std::string_view const& vertex_shader_file, std::string_view const& fragment_shader_file)
{

    const float vertices[] = {
        // positions                            // colors                           // texture coords
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f // bottom right
    };

    const unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    Shader shader("triangle");
    shader.compile_shaders("triangle", vertex_shader_file, fragment_shader_file);

    shader.bind("triangle");

    Texture tex("OpenGL/resources/textures/container.jpg");
    Texture tex2("OpenGL/resources/textures/awesomeface.png");

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    ElementBuffer ebo(indices, sizeof(indices));
    VertexBufferLayout vbl;

    vbl.push<float>(3);
    vbl.push<float>(3);
    vbl.push<float>(2);

    vao.addBuffer(vbl);

    shader.bind("triangle");
    shader.setUniformI("triangle", "texture1", 0);
    shader.setUniformI("triangle", "texture2", 1);

    while (this->window.shouldClose() != WindowState::CLOSE) {

        this->window.processInput();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        tex.activate(GL_TEXTURE0);
        tex2.activate(GL_TEXTURE1);

        la::mat4 transform;
        transform = la::translate(transform, la::vec3(0.5f, -0.5f, 0.0f));
        transform = la::rotate(transform, la::vec3(0.0, 0.0, 1.0), static_cast<float>(Window::getTime()));

        shader.bind("triangle");
        shader.setUniformM4f("triangle", "transform", la::getPointer(transform));
        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        transform = la::mat4 {};
        transform = la::translate(transform, la::vec3(-0.5f, 0.5f, 0.0f));
        transform = la::scale(transform, la::vec3 { sinf(static_cast<float>(Window::getTime())) });
        transform = la::rotate(transform, la::vec3(0.0, 0.0, 1.0), static_cast<float>(Window::getTime()));

        shader.setUniformM4f("triangle", "transform", la::getPointer(transform));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        this->window.swapBuffers();
        this->window.pollEvents();
    }

    vbo.unbind();
}

}

void framebuffer_size_callback(GLFWwindow* window [[maybe_unused]], int width, int height)
{
    glViewport(0, 0, width, height);
}
