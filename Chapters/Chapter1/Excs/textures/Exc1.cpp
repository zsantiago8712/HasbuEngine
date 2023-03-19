// CODE

/**
 * @brief  THIS code process the key input so the value can be modify
void Window::process_input2(float& value)
{
    if (glfwGetKey(this->glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->glfw_window, true);
    }

    if (glfwGetKey(this->glfw_window, GLFW_KEY_UP) == GLFW_PRESS) {
        value += 0.01f;
    }

    if (glfwGetKey(this->glfw_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        value -= 0.01f;
    }
}

*/

/**
* @brief
 shader.setUniformF("triangle", "percentagaMix", percentagaMix);

    while (this->window.should_close() != WindowState::CLOSE) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        tex.activate(GL_TEXTURE0);
        tex2.activate(GL_TEXTURE1);

        shader.bind("triangle");
        shader.setUniformF("triangle", "percentagaMix", percentagaMix);
        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        this->window.process_input2(percentagaMix);

        this->window.swap_buffers();
        this->window.poll_events();
    }

*/