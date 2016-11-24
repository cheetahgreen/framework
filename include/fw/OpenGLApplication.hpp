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

    // \brief Mouse button event. Base class should be acknowledged first
    //        about it, if it will return true, that means it was already
    //        handled and user should ignore the event.
    virtual bool onMouseButton(int button, int action, int mods);
    virtual bool onMouseMove(glm::dvec2 newPosition);
    virtual bool onScroll(double xoffset, double yoffset);
    virtual bool onKey(int key, int scancode, int action, int mods);
    virtual bool onChar(unsigned int c);
    virtual bool onResize();

    void setWindowSize(const glm::ivec2& size);
    const glm::ivec2& getWindowSize() const;

    void setWindowTitle(const std::string& title);
    const std::string& getTitle() const;

    glm::dvec2 getCurrentMousePosition() const;
    glm::dvec2 getPreviousMousePosition() const;
    glm::dvec2 getMouseMovement() const;

    static void mouseButtonCallback(
        GLFWwindow *window, int button, int action, int mods
    );
    static void mouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
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

    glm::dvec2 _previousMousePosition;
    glm::dvec2 _currentMousePosition;
    glm::dvec2 _mouseMovement;

    std::chrono::high_resolution_clock::time_point _previousFrameStartTime;
    std::chrono::high_resolution_clock::time_point _currentFrameStartTime;
    std::chrono::high_resolution_clock::duration _currentFrameDeltaTime;
};
