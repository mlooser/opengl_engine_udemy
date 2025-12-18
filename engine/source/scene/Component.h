#pragma once

namespace eng {
    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime);

        void SetOwner(GameObject* owner);
    protected:
        GameObject* owner = nullptr;
    };
}
