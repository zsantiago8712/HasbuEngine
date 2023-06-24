#pragma once

struct GLFWwindow;

namespace HasbuAPIContext {
struct Context;

void glCheckError_(const char* file, const int& line);
}

namespace HasbuRender {

void swapBuffers(GLFWwindow* native_window);

GLFWwindow* getNativeWindow(const HasbuAPIContext::Context& context);

void clearWindow();

}
