#pragma once

#include <eng.h>

class TestObject : public eng::GameObject {
public:
    std::shared_ptr<eng::Texture> loadTexture();

    TestObject();

    void Update(float deltaTime) override;

};
