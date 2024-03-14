#include <gtest/gtest.h>

#include "cp_collision.hpp"
#include "manager.hpp"
#include "main_loop.hpp"

class RendererTest : public testing::Test {
    protected:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject* obj1;
        GMObject* obj2;

        RendererTest(){}

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();

            obj1 = main_loop.create_object();
            obj1->set_position(GMVector(0, 0));
            obj1->set_dimensions(GMVector(16, 16));
            obj1->create_renderer();
        }

        void TearDown() override {
            main_loop.clear_objects();
        }
};

TEST_F(RendererTest, happy_day) {
    
}