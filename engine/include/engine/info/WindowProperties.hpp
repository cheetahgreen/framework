#pragma once
#include "glm/glm.hpp"

namespace ee
{

class IWindowProperties
{
public:
    virtual ~IWindowProperties() {}

    virtual glm::ivec2 getWindowSize() const = 0;
    virtual glm::ivec2 getFramebufferSize() const = 0;
};

class WindowProperties:
    public IWindowProperties
{
public:
    WindowProperties() {}
    virtual ~WindowProperties() {}

    virtual glm::ivec2 getWindowSize() const { return _windowSize; }
    void setWindowSize(glm::ivec2 size) { _windowSize = size; }

    virtual glm::ivec2 getFramebufferSize() const { return _framebufferSize; }
    void setFramebufferSize(glm::ivec2 size) { _framebufferSize = size; }

private:
    glm::ivec2 _windowSize;
    glm::ivec2 _framebufferSize;
};

}
