//
// Created by Marcin Lusa on 17/12/2025.
//

#include "GameObject.h"
#include <algorithm>

void eng::GameObject::Update(float deltaTime) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ( (*it)->IsAlive()) {
            (*it)->Update(deltaTime);
        }
    }

    children.erase(
        std::remove_if(
            children.begin(),
            children.end(),
            [this](const std::unique_ptr<GameObject>& child) {
                return !child->IsAlive();
            }),
        children.end());
}

void eng::GameObject::SetName(const std::string &name) {
    this->name = name;
}

const std::string & eng::GameObject::GetName() const {
    return this->name;
}

eng::GameObject * eng::GameObject::GetParent() const {
    return parent;
}

void eng::GameObject::AddChild(std::unique_ptr<GameObject> gameObject) {
    gameObject->parent = this;
    children.push_back(std::move(gameObject));
}

void eng::GameObject::ChangeParent(GameObject *gameObject, GameObject *newParent) {
    auto currentParent = gameObject->GetParent();
    if (!currentParent) {
        return;
    }

    auto child = currentParent->RemoveChild(gameObject);
    if (child) {
        newParent->AddChild(std::move(child));
    }
}

bool eng::GameObject::IsAlive() const {
    return this->isAlive;
}

void eng::GameObject::ScheduleForDestroy() {
    isAlive = false;
}

std::unique_ptr<eng::GameObject> eng::GameObject::RemoveChild(GameObject *child) {
    auto it = std::find_if(children.begin(), children.end(),
        [child](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == child;
        });

    if (it != children.end()) {
        std::unique_ptr<GameObject> removed = std::move(*it);
        removed->parent = nullptr;
        children.erase(it);
        return removed;
    }

    return nullptr;
}

eng::GameObject * eng::GameObject::CreateChildGameObject(const std::string &name) {
    return CreateChildGameObject<GameObject>(name);
}
