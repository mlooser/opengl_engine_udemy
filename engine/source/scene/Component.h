#pragma once

namespace eng {
    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime);

        void SetOwner(GameObject* owner);

        template<typename TComponent>
        static int StaticTypeId();

        virtual int GetTypeId() const = 0;
    protected:
        GameObject* owner = nullptr;

    private:
        static int nextTypeId;
    };

    template<typename TComponent>
    int Component::StaticTypeId() {
        static int typeId = nextTypeId++;
        return typeId;
    }

#define COMPONENT(ComponentClass)\
    public: \
    int TypeId() const { return StaticTypeId<ComponentClass>(); } \
    int GetTypeId() const override {return TypeId();}
}
