#pragma once

#include <chrono>
#include <string>

#include <glm/glm.hpp>

#include "OpenGLHeaders.hpp"

class OpenGLApplication
{
public:
    OpenGLApplication();
    virtual ~OpenGLApplication();

    void create();
    void destroy();
    void run();

protected:
    virtual void onCreate();
    virtual void onDestroy();
    virtual void onUpdate(
        const std::chrono::high_resolution_clock::duration& deltaTime
    );
    virtual void onRender();

    virtual void onMouseButton(int button, int action, int mods);
    virtual void onScroll(double xoffset, double yoffset);
    virtual void onKey(int key, int scancode, int action, int mods);
    virtual void onChar(unsigned int c);
    virtual void onResize();

    void setWindowSize(const glm::ivec2& size);
    const glm::ivec2& getWindowSize() const;

    void setWindowTitle(const std::string& title);
    const std::string& getTitle() const;

    glm::vec2 getMousePosition();

    static void mouseButtonCallback(
        GLFWwindow *window, int button, int action, int mods
    );
    static void scrollCallback(
        GLFWwindow *window, double xoffset, double yoffset
    );
    static void keyCallback(
        GLFWwindow *window, int key, int scancode, int action, int mods
    );
    static void charCallback(GLFWwindow *window, unsigned int c);
    static void windowSizeCallback(GLFWwindow *window, int width, int height);

    GLFWwindow *_window;

private:
    void updateFrameTimes();

    glm::ivec2 _windowSize;
    std::string _windowTitle;

    std::chrono::high_resolution_clock::time_point _previousFrameStartTime;
    std::chrono::high_resolution_clock::time_point _currentFrameStartTime;
    std::chrono::high_resolution_clock::duration _currentFrameDeltaTime;
};
