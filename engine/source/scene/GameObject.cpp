//
// Created by Marcin Lusa on 17/12/2025.
//

#include "GameObject.h"
#include <algorithm>

void eng::GameObject::Update(float deltaTime) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->IsAlive()) {
            (*it)->Update(deltaTime);
        }
        else {
            children.erase(it);
        }

    }
}

void eng::GameObject::SetName(const std::string &name) {
    this->name = name;
}

const std::string & eng::GameObject::GetName() const {
    return this->name;
}

void eng::GameObject::SetParent(GameObject *parent) {
    this->parent = parent;
    parent->AddChild(this);
}

eng::GameObject * eng::GameObject::GetParent() const {
    return parent;
}

void eng::GameObject::AddChild(GameObject *gameObject) {
    children.push_back(gameObject);
}

void eng::GameObject::ChangeParent(GameObject *gameObject, GameObject *newParent) {
    auto currentParent = gameObject->GetParent();
    currentParent->RemoveChild(gameObject);
    newParent->SetParent(gameObject);
}

bool eng::GameObject::IsAlive() const {
    return this->isAlive;
}

void eng::GameObject::ScheduleForDestroy() {
    isAlive = false;
}

void eng::GameObject::RemoveChild(GameObject *child) {
    children.erase(
        std::remove_if(children.begin(), children.end(),
            [child](const GameObject* ptr) {
                return ptr == child;
            }),
        children.end()
    );

    child->parent = nullptr;
}

eng::GameObject * eng::GameObject::CreateChildGameObject(const std::string &name) {
    return CreateChildGameObject<GameObject>(name);
}
