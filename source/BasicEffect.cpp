#include "fw/BasicEffect.hpp"
#include "fw/Shaders.hpp"
#include "fw/Resources.hpp"

#include <memory>

namespace fw
{

BasicEffect::BasicEffect()
{
}

BasicEffect::~BasicEffect()
{
}

void BasicEffect::create()
{
    createShaders();
}

void BasicEffect::destroy()
{
}

void BasicEffect::begin()
{
    _shaderProgram->use();
}

void BasicEffect::end()
{
}

void BasicEffect::createShaders()
{
    std::shared_ptr<Shader> vs = std::make_shared<Shader>();
    vs->addSourceFromFile(
        getFrameworkResourcePath("shaders/MVPTransformTexCoord.vert")
    );
    vs->compile(GL_VERTEX_SHADER);

    std::shared_ptr<Shader> fs = std::make_shared<Shader>();
    fs->addSourceFromFile(
        getFrameworkResourcePath("shaders/SolidColor.frag")
    );
    fs->compile(GL_FRAGMENT_SHADER);

    _shaderProgram = std::make_shared<ShaderProgram>();
    _shaderProgram->attach(vs.get());
    _shaderProgram->attach(fs.get());
    _shaderProgram->link();
}

}
