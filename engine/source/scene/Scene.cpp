//
// Created by Marcin Lusa on 17/12/2025.
//

#include "Scene.h"
#include "GameObject.h"


void eng::Scene::SetMainCamera(GameObject *camera) {
    mainCamera = camera;
}

eng::GameObject * eng::Scene::GetMainCamera() const {
    return mainCamera;
}
