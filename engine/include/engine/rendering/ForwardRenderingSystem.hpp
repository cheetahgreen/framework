#pragma once
#include "entityx/entityx.h"

#include "fw/UniversalPhongEffect.hpp"
#include "fw/resources/Cubemap.hpp"
#include "fw/Mesh.hpp"
#include "fw/Vertices.hpp"
#include "fw/rendering/Framebuffer.hpp"

namespace ee
{

class ForwardRenderingSystem:
    public entityx::System<ForwardRenderingSystem>
{
public:
    ForwardRenderingSystem();
    virtual ~ForwardRenderingSystem();

    void setFramebuffer(std::shared_ptr<fw::IFramebuffer> framebuffer)
    {
        _framebuffer = framebuffer;
    }

    virtual void update(
        entityx::EntityManager &entities,
        entityx::EventManager& events,
        entityx::TimeDelta
    ) override;

    void setSkybox(std::shared_ptr<fw::Cubemap> cubemap) { _cubemap = cubemap; }

private:
    std::shared_ptr<fw::Cubemap> _cubemap;
    std::shared_ptr<fw::UniversalPhongEffect> _universalPhongEffect;

    std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _box;
    std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _skybox;
    std::unique_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _plane;
    std::shared_ptr<fw::IFramebuffer> _framebuffer;

    std::shared_ptr<fw::ShaderProgram> _skyboxShader;
    GLint _skyboxViewLoc, _skyboxProjLoc, _skyboxLoc;
};

}
