#pragma once

#include <eng.h>
#include <memory>

class Game : public eng::Application {
public:
    bool Initialize(eng::Engine* owner) override;

    void Shutdown() override;

    void Update(float deltaTime) override;
};
