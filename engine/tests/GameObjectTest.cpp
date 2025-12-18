#include <gtest/gtest.h>
#include "scene/GameObject.h"
#include "scene/Scene.h"

// Test creating a child GameObject
TEST(GameObjectTest, CreateChildGameObject) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child = scene->CreateChildGameObject(nullptr, "Child1");

    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetName(), "Child1");
    EXPECT_EQ(child->GetParent(), scene);

    delete scene;
}

// Test creating multiple children
TEST(GameObjectTest, CreateMultipleChildren) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child1 = scene->CreateChildGameObject(nullptr, "Child1");
    auto* child2 = scene->CreateChildGameObject(nullptr, "Child2");

    ASSERT_NE(child1, nullptr);
    ASSERT_NE(child2, nullptr);
    EXPECT_EQ(child1->GetParent(), scene);
    EXPECT_EQ(child2->GetParent(), scene);

    delete scene;
}

// Test ChangeParent functionality
TEST(GameObjectTest, ChangeParent) {
    // Create Scene
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    // Create 2 GameObjects under the scene
    auto* parent1 = scene->CreateChildGameObject(nullptr, "Parent1");
    auto* parent2 = scene->CreateChildGameObject(nullptr, "Parent2");

    // Create a gameObject under the first parent
    auto* child = parent1->CreateChildGameObject(nullptr, "Child");

    // Verify initial parent
    EXPECT_EQ(child->GetParent(), parent1);

    // Change parent to the second parent
    scene->ChangeParent(child, parent2);

    // Verify the parent has changed
    EXPECT_EQ(child->GetParent(), parent2);

    delete scene;
}

// Test RemoveChild
TEST(GameObjectTest, RemoveChild) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child = scene->CreateChildGameObject(nullptr, "Child1");

    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->GetParent(), scene);

    auto removedChild = scene->RemoveChild(child);

    ASSERT_NE(removedChild, nullptr);
    EXPECT_EQ(removedChild->GetParent(), nullptr);
    EXPECT_EQ(removedChild.get(), child);

    delete scene;
    // removedChild is automatically deleted when unique_ptr goes out of scope
}

// Test SetName and GetName
TEST(GameObjectTest, SetAndGetName) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* gameObject = scene->CreateChildGameObject(nullptr, "InitialName");

    EXPECT_EQ(gameObject->GetName(), "InitialName");

    gameObject->SetName("NewName");
    EXPECT_EQ(gameObject->GetName(), "NewName");

    delete scene;
}

// Test IsAlive and ScheduleForDestroy
TEST(GameObjectTest, AliveStatus) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* child = scene->CreateChildGameObject(nullptr, "Child1");

    EXPECT_TRUE(child->IsAlive());

    child->ScheduleForDestroy();

    EXPECT_FALSE(child->IsAlive());

    delete scene;
}

// Test nested hierarchy
TEST(GameObjectTest, NestedHierarchy) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    auto* parent = scene->CreateChildGameObject(nullptr, "Parent");
    auto* child = parent->CreateChildGameObject(nullptr, "Child");
    auto* grandChild = child->CreateChildGameObject(nullptr, "GrandChild");

    EXPECT_EQ(parent->GetParent(), scene);
    EXPECT_EQ(child->GetParent(), parent);
    EXPECT_EQ(grandChild->GetParent(), child);

    delete scene;
}

// Test Update removes not active objects
TEST(GameObjectTest, UpdateRemovesDeadChildren) {
    auto* scene = new eng::Scene();
    scene->SetName("TestScene");

    // Create several children
    auto* child1 = scene->CreateChildGameObject(nullptr, "Child1");
    auto* child2 = scene->CreateChildGameObject(nullptr, "Child2");
    auto* child3 = scene->CreateChildGameObject(nullptr, "Child3");
    auto* child4 = scene->CreateChildGameObject(nullptr, "Child4");

    // Mark some children for destruction
    child1->ScheduleForDestroy();
    child3->ScheduleForDestroy();

    // child2 and child4 should still be alive
    EXPECT_FALSE(child1->IsAlive());
    EXPECT_TRUE(child2->IsAlive());
    EXPECT_FALSE(child3->IsAlive());
    EXPECT_TRUE(child4->IsAlive());

    // Call Update - this should remove dead children
    scene->Update(0.0f);

    // After Update, only child2 and child4 should remain
    // We can verify by trying to get their parents
    // Dead children should have been deleted
    EXPECT_EQ(child2->GetParent(), scene);
    EXPECT_EQ(child4->GetParent(), scene);

    delete scene;
}
