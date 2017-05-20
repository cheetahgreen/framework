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

    void setIrradianceMap(std::shared_ptr<fw::Cubemap> cubemap)
    {
        _irradianceMap = cubemap;
    }

    void setPrefilterMap(std::shared_ptr<fw::Cubemap> cubemap)
    {
        _prefilterMap = cubemap;
    }

    void setBrdfLut(std::shared_ptr<fw::Texture> texture)
    {
        _brdfLut = texture;
    }

private:
    std::shared_ptr<fw::Cubemap> _cubemap;
    std::shared_ptr<fw::Cubemap> _irradianceMap;
    std::shared_ptr<fw::Cubemap> _prefilterMap;
    std::shared_ptr<fw::Texture> _brdfLut;

    std::shared_ptr<fw::UniversalPhongEffect> _universalPhongEffect;

    std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _box;
    std::shared_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _skybox;
    std::unique_ptr<fw::Mesh<fw::VertexNormalTexCoords>> _plane;
    std::shared_ptr<fw::IFramebuffer> _framebuffer;

    std::shared_ptr<fw::ShaderProgram> _skyboxShader;
    GLint _skyboxViewLoc, _skyboxProjLoc, _skyboxLoc;
};

}
