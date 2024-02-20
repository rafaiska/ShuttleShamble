#include <gtest/gtest.h>

#include "cp_collision.hpp"
#include "manager.hpp"
#include "main_loop.hpp"

class CollisionTest : public testing::Test {
    private:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject obj1, obj2;
    
    protected:

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();

            obj1.set_position(GMVector(0, 0));
            obj1.set_position(GMVector(5, 5));
        }

        void TearDown() override {
            delete manager;
        }

        TEST_F(CollisionTest, happy_day) {
            obj1.set_speed(GMVector(5, 5));
            main_loop.tick(1.0);
            
        }
};