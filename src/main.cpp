#include "manager.hpp"
#include "main_loop.hpp"

int main(int argc, char* argv[]) {
    GMManager::get_instance()->start_test_services();
    GMMainLoop main_loop = GMMainLoop();
    main_loop.main_loop();
}