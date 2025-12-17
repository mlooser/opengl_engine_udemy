#pragma once
#include <string>
#include <vector>
#include <memory>

namespace eng {
    class GameObject {

    public:
        virtual ~GameObject() = default;

        virtual void Update(float deltaTime);

        void SetName(const std::string &name);
        const std::string &GetName() const;

        void SetParent(GameObject *parent);
        GameObject *GetParent() const;
        void AddChild(std::unique_ptr<GameObject> gameObject);
        void ChangeParent(GameObject* gameObject, GameObject* newParent);

        bool IsAlive() const;
        void ScheduleForDestroy();

        std::unique_ptr<GameObject> RemoveChild(GameObject *child);

        GameObject* CreateChildGameObject(const std::string& name);

        template<typename T, typename = std::enable_if<std::is_base_of_v<GameObject, T>>>
        T* CreateChildGameObject(const std::string& name);

    protected:
        GameObject() = default;

    private:
        std::string name;
        GameObject* parent = nullptr;
        std::vector<std::unique_ptr<GameObject>> children;
        bool isAlive = true;
    };

    template<typename T, typename>
    T* GameObject::CreateChildGameObject(const std::string& name) {
        auto gameObject = std::unique_ptr<T>(new T());
        T* rawPtr = gameObject.get();
        rawPtr->SetName(name);
        rawPtr->SetParent(this);
        children.push_back(std::move(gameObject));

        return rawPtr;
    }
}
