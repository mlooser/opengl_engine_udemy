#pragma once
#include <string>
#include <vector>

namespace eng {
    class GameObject {

    public:
        virtual ~GameObject() = default;

        virtual void Update(float deltaTime);

        void SetName(const std::string &name);
        const std::string &GetName() const;

        void SetParent(GameObject *parent);
        GameObject *GetParent() const;
        void AddChild(GameObject * gameObject);
        void ChangeParent(GameObject* gameObject, GameObject* newParent);

        bool IsAlive() const;
        void ScheduleForDestroy();

        void RemoveChild(GameObject *child);

        GameObject* CreateChildGameObject(const std::string& name);

        template<typename T, typename = std::enable_if<std::is_base_of_v<GameObject, T>>>
        T* CreateChildGameObject(const std::string& name);

    protected:
        GameObject() = default;

    private:
        std::string name;
        GameObject* parent;
        std::vector<GameObject*> children;
        bool isAlive = true;
    };

    template<typename T, typename>
    T* GameObject::CreateChildGameObject(const std::string& name) {

        T* gameObject = new T();
        gameObject->SetName(name);
        gameObject->SetParent(this);
        children.push_back(gameObject);

        return gameObject;
    }
}
