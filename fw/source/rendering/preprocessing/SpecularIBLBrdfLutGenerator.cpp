#pragma once
#include "fw/rendering/preprocessing/SpecularIBLBrdfLutGenerator.hpp"
#include "fw/Resources.hpp"
#include "fw/DebugShapes.hpp"

namespace fw
{

SpecularIBLBrdfLutGenerator::SpecularIBLBrdfLutGenerator()
{
    _shaderProgram = std::make_unique<ShaderProgram>(
        getFrameworkResourcePath("shaders/SpecularIBLBrdfLut.sbl")
    );

    _quad = fw::createQuad2D({2.0f, 2.0f});
}

SpecularIBLBrdfLutGenerator::~SpecularIBLBrdfLutGenerator()
{
}

void SpecularIBLBrdfLutGenerator::render()
{
    _shaderProgram->use();
    _quad->render();
}

}
