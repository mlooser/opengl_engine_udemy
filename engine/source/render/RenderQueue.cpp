//
// Created by Marcin Lusa on 17/12/2025.
//

#include "RenderQueue.h"

#include "render/Mesh.h"
#include "render/Material.h"
#include "graphics/GraphicsAPI.h"

void eng::RenderQueue::Submit(const RenderCommand &command) {
    renderCommands.push_back(command);
}

void eng::RenderQueue::Draw(GraphicsAPI &graphicsAPI) {
    for (auto& command: renderCommands) {
        graphicsAPI.BindMaterial(command.material);
        graphicsAPI.BindMesh(command.mesh);
        graphicsAPI.DrawMesh(command.mesh);
    }

    renderCommands.clear();
}
