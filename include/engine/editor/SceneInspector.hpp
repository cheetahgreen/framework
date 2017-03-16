#pragma once
#include "entityx/entityx.h"
#include "fw/editor/LightEditor.hpp"

namespace ee
{

class SceneInspector
{
public:
    explicit SceneInspector(entityx::EntityManager* entityManager);
    ~SceneInspector();

    bool& getShowFlag() { return _inspectorEnabled; }
    void show();

protected:
    void showMenu();
    void showEntitiesList();
    void showComponentsList();

    void showEntityInfoComponent();
    void showTransformComponent();

    void createEmptyEntity();
    void createLight();

private:
    entityx::EntityManager* _entityManager;
    entityx::Entity _selectedEntity;
    bool _inspectorEnabled;

    fw::LightEditor _lightEditor;
};

}
