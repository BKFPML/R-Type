#include <gtest/gtest.h>
#include "../engine/includes/ECS.hpp"

TEST(ECSTest, CreateEntity) {
    ECS ecs;
    ECS::Entity entity1 = ecs.createEntity();
    ECS::Entity entity2 = ecs.createEntity();
    EXPECT_EQ(entity1, 0);
    EXPECT_EQ(entity2, 1);
    EXPECT_NE(entity1, entity2);
}

TEST(ECSTest, CreatePosComponent) {
    ECS ecs;
    ECS::Entity entity = ecs.createEntity();

    ecs.registerComponent<Position>();

    ecs.addComponent(entity, Position{1, 2});

    Position *pos = ecs.getComponent<Position>(entity);

    EXPECT_EQ(pos->x, 1);
    EXPECT_EQ(pos->y, 2);
}

TEST(ECSTest, CreateHealthComponent) {
    ECS ecs;
    ECS::Entity entity = ecs.createEntity();

    ecs.registerComponent<Health>();

    ecs.addComponent(entity, Health{50});

    Health *health = ecs.getComponent<Health>(entity);

    EXPECT_EQ(health->hp, 50);
}

TEST(ECSTest, CreateAttackComponent) {
    ECS ecs;
    ECS::Entity entity = ecs.createEntity();

    ecs.registerComponent<Attack>();

    ecs.addComponent(entity, Attack{10});

    Attack *attack = ecs.getComponent<Attack>(entity);

    EXPECT_EQ(attack->damage, 10);
}

TEST(ECSTest, CreateStatusComponent) {
    ECS ecs;
    ECS::Entity entity = ecs.createEntity();

    ecs.registerComponent<Status>();

    ecs.addComponent(entity, Status{StatusType::ALLY});

    Status *status = ecs.getComponent<Status>(entity);

    EXPECT_EQ(status->status, StatusType::ALLY);
}

TEST(ECSTest, CreateRotationComponent) {
    ECS ecs;
    ECS::Entity entity = ecs.createEntity();

    ecs.registerComponent<Rotation>();

    ecs.addComponent(entity, Rotation{45});

    Rotation *rotation = ecs.getComponent<Rotation>(entity);

    EXPECT_EQ(rotation->angle, 45);
}
