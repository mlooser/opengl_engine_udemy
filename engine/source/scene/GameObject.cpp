//
// Created by Marcin Lusa on 17/12/2025.
//

#include "GameObject.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

void eng::GameObject::Update(float deltaTime) {
    for (const auto &it: components) {
        it->Update(deltaTime);
    }

    for (const auto &it: children) {
        if (it->IsAlive()) {
            it->Update(deltaTime);
        }
    }

    children.erase(
        std::remove_if(
            children.begin(),
            children.end(),
            [](const std::unique_ptr<GameObject> &child) {
                return !child->IsAlive();
            }),
        children.end());
}

void eng::GameObject::SetName(const std::string &name) {
    this->name = name;
}

const std::string &eng::GameObject::GetName() const {
    return this->name;
}

eng::GameObject *eng::GameObject::GetParent() const {
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
                           [child](const std::unique_ptr<GameObject> &ptr) {
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

eng::GameObject *eng::GameObject::CreateChildGameObject(Engine *engine, const std::string &name) {
    return CreateChildGameObject<GameObject>(engine, name);
}

glm::mat4 eng::GameObject::GetLocalTransform() const {
    glm::mat4 localTransform = glm::mat4(1.0f);

    localTransform = glm::translate(localTransform, transform.position);

    localTransform = glm::rotate(localTransform, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    localTransform = glm::rotate(localTransform, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    localTransform = glm::rotate(localTransform, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    localTransform = glm::scale(localTransform, transform.scale);

    return localTransform;
}

glm::mat4 eng::GameObject::GetWorldTransform() const {
    if (parent) {
        return parent->GetWorldTransform() * GetLocalTransform();
    }

    return GetLocalTransform();
}

eng::Engine * eng::GameObject::GetEngine() const {
    return engine;
}

void eng::GameObject::SetPosition(const glm::vec3 &vec) {
    transform.position = vec;
}

eng::Transform& eng::GameObject::GetTransform() {
    return transform;
}

const eng::Transform& eng::GameObject::GetTransform() const {
    return transform;
}
