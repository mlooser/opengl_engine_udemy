//
// Created by Marcin Lusa on 18/12/2025.
//

#include "Component.h"

void eng::Component::Update(float deltaTime) {
}

void eng::Component::SetOwner(GameObject *owner) {
    this->owner = owner;
}
