#pragma once

#include "glm/glm.hpp"

namespace fw
{

class IViewport
{
public:
    virtual ~IViewport() {}

    virtual glm::ivec2 getViewportPos() const = 0;
    virtual glm::ivec2 getViewportSize() const = 0;
};

class Viewport:
    public IViewport
{
public:
    Viewport() {}

    Viewport(const glm::ivec2& position, const glm::ivec2& size):
        _position{position},
        _size{size}
    {
    }

    virtual glm::ivec2 getViewportPos() const { return _position; }
    virtual glm::ivec2 getViewportSize() const { return _size; }

    void setViewportPos(const glm::ivec2& position) { _position = position; }
    void setViewportSize(const glm::ivec2& size) { _size = size; }

private:
    glm::ivec2 _position;
    glm::ivec2 _size;
};

}
