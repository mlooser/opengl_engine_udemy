#pragma once
#include "GameObject.h"


namespace eng {
    class Scene : public GameObject {
    public:
        Scene() = default;
        virtual ~Scene() = default;
    };
}
