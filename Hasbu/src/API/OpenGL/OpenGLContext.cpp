#include "Application/WindowData.hpp"
#include "Renderer/Context.hpp"
#include "Utilities/Logger.hpp"
#include <GL/glew.h>
#include <string_view>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace HasbuAPIContext {

static GLFWwindow* createNativeWindow(const unsigned int width, const unsigned int height, const std::string_view& name);

static constexpr unsigned int OPENGL_MAJOR_VERSION = 4;
static constexpr unsigned int OPENGL_MINOR_VERSION = 1;

enum class API {
    GL = 0X0,
    VK = 0X1,
};

struct Context {

    explicit Context(const unsigned int width, const unsigned int height, const std::string_view& name);
    ~Context();

    void createOpenGLContext();

    const API api = API::GL;
    GLFWwindow* native_widow = nullptr;
};

Context::Context(const unsigned int width, const unsigned int height, const std::string_view& name)
    : native_widow(createNativeWindow(width, height, name))
{
    this->createOpenGLContext();
}

void Context::createOpenGLContext()
{
    glfwMakeContextCurrent(this->native_widow);

    HASBU_ASSERT(GLEW_OK != glewInit(), "GLEW (OpenGL) failed to load")

    glEnable(GL_DEPTH_TEST);
    HASBU_INFO("OPENGL succes to load {}", reinterpret_cast<const char*>((glGetString(GL_VERSION))));
}

Context::~Context()
{
    glfwDestroyWindow(this->native_widow);
    glfwTerminate();
}

static GLFWwindow* createNativeWindow(const unsigned int width, const unsigned int height, const std::string_view& name)
{
    HASBU_ASSERT(!glfwInit(), "GLFW failed to initilized")

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
    HASBU_ASSERT(window == nullptr, "GLFW filaed to create a window")

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    HASBU_INFO("GLFW SUCCES TO INITIAZED AND CREATE A WINDOW");
    return window;
}

void glCheckError_(const char* file, const int& line)
{
    unsigned int severity;
    while ((severity = glGetError()) != GL_NO_ERROR) {

        switch (severity) {
        case GL_INVALID_ENUM:
            HASBU_ERROR("[OPENGL]: INVALID_ENUM [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_VALUE:
            HASBU_ERROR("[OPENGL]: INVALID_VALUE [FILE: {}; LINE: {}], file, line");
            break;
        case GL_STACK_OVERFLOW:
            HASBU_WARNING("[OPENGL]: STACK_OVERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_OUT_OF_MEMORY:
            HASBU_ERROR("[OPENGL]: STACK_UNDERFLOW [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_OPERATION [FILE: {}; LINE: {}]", file, line);
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            HASBU_ERROR("[OPENGL]: INVALID_FRAMEBUFFER [FILE: {}; LINE: {}]", file, line);
            break;
        default:
            HASBU_DEBUG("[OPENGL]: UNKNOWN_ERROR [FILE: {}; LINE: {}]", file, line);
            break;
        }
    }
}

}

namespace Hasbu {

WindowData::WindowData(const unsigned int height, const unsigned int width)
    : width(width)
    , height(height)
    , context(HasbuUtils::createUnique<HasbuAPIContext::Context>(height, width, this->name)) {};

WindowData::WindowData()
    : context(HasbuUtils::createUnique<HasbuAPIContext::Context>(this->width, this->height, this->name)) {};

}
namespace HasbuRender {

void swapBuffers(GLFWwindow* native_window)
{
    glfwSwapBuffers(native_window);
}

GLFWwindow* getNativeWindow(const HasbuAPIContext::Context& context)
{
    return context.native_widow;
}

void clearWindow()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
