#include "cp_collision.hpp"

GMCpCollider::GMCpCollider(GMRect transform, GMVector global_position)
{
    this->transform = transform;
    this->position = global_position;
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
    GMRect this_global_rect = GMRect(transform.w, transform.h,
        new_position.x + transform.x, new_position.y + transform.y);
    GMRect other_transform = other.get_transform();
    GMVector other_new_position = other.get_new_position();
    GMRect other_global_rect = GMRect(other_transform.w, other_transform.h,
        other_new_position.x + other_transform.x, other_new_position.y + other_transform.y);
    return rect_intersection(this_global_rect, other_global_rect) != GMRect();
}

void GMCpCollider::add_collided_with(GMCpCollider* other)
{
    this->collided_with_others.push_back(other);
}
