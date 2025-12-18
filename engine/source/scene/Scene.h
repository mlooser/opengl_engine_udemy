#pragma once
#include "GameObject.h"


namespace eng {
    class Scene : public GameObject {
    public:
        Scene() = default;

        ~Scene() override = default;

        void SetMainCamera(GameObject* camera);
        GameObject* GetMainCamera() const;

    private:
        GameObject* mainCamera;
    };
}
