#pragma once

namespace eng {
    class Engine;
    class Application {
        public:
        virtual ~Application() = default;

        virtual bool Initialize(Engine* owner);
        virtual void Shutdown() = 0;
        virtual void Update(float deltaTime) = 0;

        void SetNeedsToBeClosed(bool needsToBeClosed);
        bool NeedsToBeClosed() const;

    private:
        bool needsToBeClosed = false;

    protected:
        Engine* owner = nullptr;
    };
}