#include "cp_collision.hpp"

void GMCpCollider::update(float delta) {
    new_position = position + (speed * delta);
}

void GMCpCollider::set_speed(GMVector new_speed) {
    speed = new_speed;
}

bool GMCpCollider::collided_with(const GMCpCollider& other) {
    return false;
}

void GMCpCollider::set_collided_with(GMCpCollider *other)
{
    this->collided_with_other = other;
}
