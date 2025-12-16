#pragma once

namespace eng {
    class Application {
        public:
        virtual ~Application() = default;

        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;
        virtual void Update(float deltaTime) = 0;

        void SetNeedsToBeClosed(bool needsToBeClosed);
        bool NeedsToBeClosed() const;

    private:
        bool needsToBeClosed = true;
    };
}