#pragma once

#include <eng.h>

class Game : public eng::Application {
public:
    bool Initialize() override;

    void Shutdown() override;

    void Update(float deltaTime) override;
};
