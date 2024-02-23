#include "cp_collision.hpp"

void GMCpCollider::update(float delta) {
    position = position + (speed * delta);
}

void GMCpCollider::set_speed(GMVector new_speed) {
}

bool GMCpCollider::collided_with(GMCpCollider other) {
    return false;
}
