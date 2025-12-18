//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Application.h"

bool eng::Application::Initialize(Engine *owner) {
    this->owner = owner;
    return true;
}

void eng::Application::SetNeedsToBeClosed(bool needsToBeClosed) {
    this->needsToBeClosed = needsToBeClosed;
}

bool eng::Application::NeedsToBeClosed() const {
    return needsToBeClosed;
}

eng::Scene & eng::Application::GetScene() {
    return scene;
}


