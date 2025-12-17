#include <gtest/gtest.h>
#include "scene/Scene.h"
#include "scene/GameObject.h"

// Test Scene creation without parent
TEST(SceneTest, CreateSceneWithoutParent) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    ASSERT_NE(scene, nullptr);
    EXPECT_EQ(scene->GetName(), "TestScene");
    EXPECT_EQ(scene->GetParent(), nullptr);

    delete scene;
}

// Test Scene can have children
TEST(SceneTest, SceneCanHaveChildren) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child1 = scene->CreateChildGameObject("Child1");
    auto* child2 = scene->CreateChildGameObject("Child2");

    ASSERT_NE(child1, nullptr);
    ASSERT_NE(child2, nullptr);
    EXPECT_EQ(child1->GetParent(), scene);
    EXPECT_EQ(child2->GetParent(), scene);

    delete scene;
}

// Test Scene inherits GameObject functionality
TEST(SceneTest, SceneInheritsGameObjectFunctionality) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    EXPECT_TRUE(scene->IsAlive());

    scene->ScheduleForDestroy();

    EXPECT_FALSE(scene->IsAlive());

    delete scene;
}

// Test Scene can have nested hierarchy
TEST(SceneTest, SceneWithNestedHierarchy) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* parent = scene->CreateChildGameObject("Parent");
    auto* child = parent->CreateChildGameObject("Child");
    auto* grandChild = child->CreateChildGameObject("GrandChild");

    EXPECT_EQ(parent->GetParent(), scene);
    EXPECT_EQ(child->GetParent(), parent);
    EXPECT_EQ(grandChild->GetParent(), child);

    delete scene;
}

// Test removing children from Scene
TEST(SceneTest, RemoveChildFromScene) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child = scene->CreateChildGameObject("Child");

    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetParent(), scene);

    auto removedChild = scene->RemoveChild(child);

    ASSERT_NE(removedChild, nullptr);
    EXPECT_EQ(removedChild->GetParent(), nullptr);

    delete scene;
    // removedChild is automatically deleted when unique_ptr goes out of scope
}
