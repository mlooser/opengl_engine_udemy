//
// Created by Marcin Lusa on 18/12/2025.
//

#include "MeshComponent.h"

#include "render/RenderQueue.h"
#include "scene/GameObject.h"
#include "Engine.h"

eng::MeshComponent::MeshComponent(const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material)
    : mesh(mesh), material(material) {
}

void eng::MeshComponent::Update(float deltaTime) {
    Component::Update(deltaTime);

    eng::RenderCommand renderCommand{
        mesh.get(),
        material.get(),
        owner->GetWorldTransform()
    };

    owner->GetEngine()->GetRenderQueue().Submit(renderCommand);
}
