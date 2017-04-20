#pragma once
#include "entityx/entityx.h"
#include "fwui/LightEditor.hpp"
#include "fwui/MaterialEditor.hpp"
#include "fwui/editors/RenderMeshEditor.hpp"
#include "fwui/editors/AreaLightEditor.hpp"
#include "fw/resources/TextureManager.hpp"
#include "fw/models/StaticModelFactory.hpp"

namespace ee
{

class SceneInspector
{
public:
    SceneInspector(
        fw::VirtualFilesystem& vfs,
        std::shared_ptr<fw::ITextureManagerWithInspection> textureManager,
        std::shared_ptr<fw::StaticModelFactory> staticModelFactory,
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
    void showAreaLightComponent();
    void showMeshComponent();
    void showMaterialComponent();

    void createEmptyEntity();
    void createLight();

    void attachAreaLight();

private:
    entityx::EntityManager* _entityManager;

    fw::VirtualFilesystem& _vfs;
    std::shared_ptr<fw::ITextureManagerWithInspection> _textureManager;
    std::shared_ptr<fw::StaticModelFactory> _staticModelFactory;

    entityx::Entity _selectedEntity;
    bool _inspectorEnabled;

    fw::LightEditor _lightEditor;
    fwui::RenderMeshEditor _renderMeshEditor;
    fw::MaterialEditor _materialEditor;
    fwui::AreaLightEditor _areaLightEditor;
};

}
