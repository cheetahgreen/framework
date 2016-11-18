#include "OpenGLApplication.hpp"
#include <string>

using namespace std;

OpenGLApplication::OpenGLApplication():
    _windowSize{800, 600},
    _windowTitle{"Framework Application"}
{
}

OpenGLApplication::~OpenGLApplication()
{
    destroy();
}

void OpenGLApplication::create()
{
    if (!glfwInit())
    {
        throw string("Cannot initialize GLFW3.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = glfwCreateWindow(
        _windowSize.x,
        _windowSize.y,
        _windowTitle.c_str(),
        nullptr,
        nullptr
    );

    if (!_window)
    {
        glfwTerminate();
        throw string("Cannot create GLFW3 window.");
    }

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSetWindowUserPointer(_window, static_cast<void*>(this));

    glfwSetMouseButtonCallback(_window, OpenGLApplication::mouseButtonCallback);
    glfwSetScrollCallback(_window, OpenGLApplication::scrollCallback);
    glfwSetKeyCallback(_window, OpenGLApplication::keyCallback);
    glfwSetCharCallback(_window, OpenGLApplication::charCallback);

    onCreate();
}

void OpenGLApplication::destroy()
{
    onDestroy();
    glfwTerminate();
}

void OpenGLApplication::run()
{
    _currentFrameStartTime = _previousFrameStartTime =
        std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();
        updateFrameTimes();

        onUpdate(_currentFrameDeltaTime);
        onRender();

        glfwSwapBuffers(_window);
    }

    destroy();
}

void OpenGLApplication::onCreate()
{
}

void OpenGLApplication::onDestroy()
{
}

void OpenGLApplication::onUpdate(
    const std::chrono::high_resolution_clock::duration& deltaTime
)
{
}

void OpenGLApplication::onRender()
{
}

void OpenGLApplication::onMouseButton(int button, int action, int mods)
{
}

void OpenGLApplication::onScroll(double xoffset, double yoffset)
{
}

void OpenGLApplication::onKey(int key, int scancode, int action, int mods)
{
}

void OpenGLApplication::onChar(unsigned int c)
{
}

void OpenGLApplication::onResize()
{
}

void OpenGLApplication::setWindowSize(const glm::ivec2& size)
{
    _windowSize = size;
    if (_window != nullptr)
    {
        glfwSetWindowSize(_window, _windowSize.x, _windowSize.y);
    }
}

const glm::ivec2& OpenGLApplication::getWindowSize() const
{
    return _windowSize;
}

void OpenGLApplication::setWindowTitle(const std::string& title)
{
    _windowTitle = title;
    if (_window != nullptr)
    {
        glfwSetWindowTitle(_window, _windowTitle.c_str());
    }
}

const std::string& OpenGLApplication::getTitle() const
{
    return _windowTitle;
}


void OpenGLApplication::mouseButtonCallback(
    GLFWwindow *window, int button, int action, int mods
)
{
    auto app = static_cast<OpenGLApplication*>(
        glfwGetWindowUserPointer(window)
    );

    app->onMouseButton(button, action, mods);
}

void OpenGLApplication::scrollCallback(
    GLFWwindow *window, double xoffset, double yoffset
)
{
    auto app = static_cast<OpenGLApplication*>(
        glfwGetWindowUserPointer(window)
    );

    app->onScroll(xoffset, yoffset);
}

void OpenGLApplication::keyCallback(
    GLFWwindow *window, int key, int scancode, int action, int mods
)
{
    auto app = static_cast<OpenGLApplication*>(
        glfwGetWindowUserPointer(window)
    );

    app->onKey(key, scancode, action, mods);
}

void OpenGLApplication::charCallback(GLFWwindow *window, unsigned int c)
{
    auto app = static_cast<OpenGLApplication*>(
        glfwGetWindowUserPointer(window)
    );

    app->onChar(c);
}

void OpenGLApplication::windowSizeCallback(
    GLFWwindow *window,
    int width,
    int height
)
{
    auto app = static_cast<OpenGLApplication*>(
        glfwGetWindowUserPointer(window)
    );

    app->setWindowSize({width, height});
    app->onResize();
}

glm::vec2 OpenGLApplication::getMousePosition()
{
    double xPos, yPos;
    glfwGetCursorPos(_window, &xPos, &yPos);
    return glm::vec2((float)xPos, (float)yPos);
}

void OpenGLApplication::updateFrameTimes()
{
    _previousFrameStartTime = _currentFrameStartTime;
    _currentFrameStartTime = std::chrono::high_resolution_clock::now();
    _currentFrameDeltaTime =
        _currentFrameStartTime - _previousFrameStartTime;
}

