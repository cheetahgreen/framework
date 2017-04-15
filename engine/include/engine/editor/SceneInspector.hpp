#pragma once
#include "entityx/entityx.h"
#include "fwui/LightEditor.hpp"
#include "fwui/MaterialEditor.hpp"
#include "fwui/editors/RenderMeshEditor.hpp"
#include "fw/resources/TextureManager.hpp"

namespace ee
{

class SceneInspector
{
public:
    SceneInspector(
        std::shared_ptr<fw::ITextureManagerWithInspection> textureManager,
        entityx::EntityManager* entityManager
    );

    ~SceneInspector();

    bool& getShowFlag() { return _inspectorEnabled; }
    void show();

protected:
    void showMenu();
    void showEntitiesList();
    void showComponentsList();

    void showEntityInfoComponent();
    void showTransformComponent();
    void showLightComponent();
    void showMeshComponent();
    void showMaterialComponent();

    void createEmptyEntity();
    void createLight();

private:
    entityx::EntityManager* _entityManager;
    std::shared_ptr<fw::ITextureManagerWithInspection> _textureManager;

    entityx::Entity _selectedEntity;
    bool _inspectorEnabled;

    fw::LightEditor _lightEditor;
    fwui::RenderMeshEditor _renderMeshEditor;
    fw::MaterialEditor _materialEditor;
};

}
