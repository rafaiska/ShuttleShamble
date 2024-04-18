#include "cp_collision.hpp"

GMCpCollider::GMCpCollider(GMRect transform)
{
    this->transform = transform;
    this->position = get_position_from_rect(transform);
    this->new_position = position;
    this->speed = GMVector(0, 0);
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
    return rect_intersection(transform, other.transform) != GMRect();
}

void GMCpCollider::add_collided_with(GMCpCollider* other)
{
    this->collided_with_others.push_back(other);
}
