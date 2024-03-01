#include <gtest/gtest.h>

#include "cp_collision.hpp"
#include "manager.hpp"
#include "main_loop.hpp"

class CollisionTest : public testing::Test {
    protected:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject* obj1;
        GMObject* obj2;

        CollisionTest(){}

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();

            obj1 = main_loop.create_object();
            obj1->set_position(GMVector(0, 0));
            obj1->set_dimensions(GMVector(16, 16));
            obj1->create_collider();

            obj2 = main_loop.create_object();
            obj2->set_position(GMVector(16, 16));
            obj2->set_dimensions(GMVector(16, 16));
            obj2->create_collider();
        }

        void TearDown() override {
            main_loop.clear_objects();
        }
};

TEST_F(CollisionTest, happy_day) {
    GMCpCollider* collider = obj1->get_collider();
    collider->set_speed(GMVector(5, 5));
    main_loop.tick(1.0);
    ASSERT_EQ(collider->get_collided_with(), obj2->get_collider());
}