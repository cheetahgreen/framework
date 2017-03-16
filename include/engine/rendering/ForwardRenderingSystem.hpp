#pragma once
#include "entityx/entityx.h"
#include "fw/UniversalPhongEffect.hpp"

namespace ee
{

class ForwardRenderingSystem:
    public entityx::System<ForwardRenderingSystem>
{
public:
    ForwardRenderingSystem();
    virtual ~ForwardRenderingSystem();

    virtual void update(
        entityx::EntityManager &entities,
        entityx::EventManager& events,
        entityx::TimeDelta
    ) override;

private:
    std::shared_ptr<fw::UniversalPhongEffect> _universalPhongEffect;
};

}
