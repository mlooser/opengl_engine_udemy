#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace eng {
    class Engine;

    class GameObject {
    public:
        virtual ~GameObject() = default;

        virtual void Update(float deltaTime);

        void SetName(const std::string &name);

        const std::string &GetName() const;

        GameObject *GetParent() const;

        void AddChild(std::unique_ptr<GameObject> gameObject);

        void ChangeParent(GameObject *gameObject, GameObject *newParent);

        bool IsAlive() const;

        void ScheduleForDestroy();

        std::unique_ptr<GameObject> RemoveChild(GameObject *child);

        GameObject *CreateChildGameObject(Engine* engine, const std::string &name);

        template<typename T, typename = std::enable_if<std::is_base_of_v<GameObject, T> > >
        T *CreateChildGameObject(Engine* engine, const std::string &name);

        glm::mat4 GetLocalTransform() const;
        glm::mat4 GetWorldTransform() const;

    protected:
        GameObject() = default;
        Engine* engine;

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

    private:
        std::string name;
        GameObject *parent = nullptr;
        std::vector<std::unique_ptr<GameObject> > children;
        bool isAlive = true;
    };

    template<typename T, typename>
    T *GameObject::CreateChildGameObject(Engine* engine, const std::string &name) {
        auto gameObject = std::unique_ptr<T>(new T());
        T *rawPtr = gameObject.get();
        rawPtr->SetName(name);
        rawPtr->parent = this;
        rawPtr->engine = engine;

        children.push_back(std::move(gameObject));

        return rawPtr;
    }
}
