#pragma once
#include "TextureGeneratorBase.hpp"
#include "fw/Mesh.hpp"
#include "fw/Vertices.hpp"

namespace fw
{

class SpecularIBLBrdfLutGenerator:
    public TextureGeneratorBase
{
public:
    SpecularIBLBrdfLutGenerator();
    virtual ~SpecularIBLBrdfLutGenerator();

protected:
    virtual void render();

private:
    std::unique_ptr<ShaderProgram> _shaderProgram;
    std::shared_ptr<Mesh<StandardVertex2D>> _quad;
};

}
