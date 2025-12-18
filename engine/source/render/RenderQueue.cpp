//
// Created by Marcin Lusa on 17/12/2025.
//

#include "RenderQueue.h"

#include "render/Mesh.h"
#include "render/Material.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"

void eng::RenderQueue::Submit(const RenderCommand &command) {
    renderCommands.push_back(command);
}

void eng::RenderQueue::Draw(GraphicsAPI &graphicsAPI, const CameraData& cameraData) {
    for (auto& command: renderCommands) {
        graphicsAPI.BindMaterial(command.material);
        auto shaderProgram = command.material->GetShaderProgram();

        shaderProgram->SetUniform("uModel", command.modelMatrix);
        shaderProgram->SetUniform("uView", cameraData.viewMatrix);
        shaderProgram->SetUniform("uProjection", cameraData.projectionMatrix);

        graphicsAPI.BindMesh(command.mesh);
        graphicsAPI.DrawMesh(command.mesh);
    }

    renderCommands.clear();
}
