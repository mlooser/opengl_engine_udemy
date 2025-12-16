#pragma once

namespace eng {
    class Application {
        public:
        virtual bool Initialize();
        virtual void Shutdown();
        virtual void Update(float deltaTime);

        void SetNeedsToBeClosed(bool needsToBeClosed);
        bool NeedsToBeClosed() const;

    private:
        bool needsToBeClosed;
    };
}