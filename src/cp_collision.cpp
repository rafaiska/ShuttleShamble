#include "cp_collision.hpp"

GMCpCollider::GMCpCollider(const GMVector& position, float aura_radius)
{
    this->position = position;
    this->new_position = position;
    this->speed = GMVector(0, 0);
    this->aura_radius = aura_radius;
}

void GMCpCollider::update(float delta) {
    new_position = position + (speed * delta);
}

bool GMCpCollider::moved()
{
    return(new_position == position);
}

void GMCpCollider::set_speed(GMVector new_speed) {
    speed = new_speed;
}

bool GMCpCollider::collided_with(const GMCpCollider& other) {
    float distance_between_colliders = distance_between(position, other.get_position());
    return distance_between_colliders < aura_radius + other.get_aura_radius();
}

void GMCpCollider::set_collided_with(GMCpCollider *other)
{
    this->collided_with_other = other;
}
