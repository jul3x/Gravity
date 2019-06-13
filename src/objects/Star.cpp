//
// Created by jprolejko on 12.06.19.
//


#include <Config.h>

#include <objects/Star.h>


Star::Star(const sf::Vector2f &position, const sf::Vector2f &velocity, const float radius, const float color_alpha) :
    position_(position), velocity_(velocity), radius_(radius), color_alpha_(color_alpha), alfa_change_velocity_(100.0f) {}

const sf::Vector2f& Star::getPosition() const {
    return position_;
}

void Star::setPosition(const sf::Vector2f &position) {
    position_ = position;
}

void Star::update(float time_elapsed) {
    // alpha change
    if (color_alpha_ >= 255 || color_alpha_ <= 0) 
    {
        alfa_change_velocity_ = -alfa_change_velocity_;
    }
    
    color_alpha_ += static_cast<int>(alfa_change_velocity_ * time_elapsed);
    position_ = position_ + time_elapsed * velocity_;

    color_alpha_ = std::max(std::min(255, color_alpha_), 0);

    // infinite loop of movement
    if ((position_.x - radius_ * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_WIDTH_PIXELS_)
    {
        position_.x = - radius_ * Config::OBJECT_ZOOM_;
    }

    if ((position_.y - radius_ * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_HEIGHT_PIXELS_)
    {
        position_.y = - radius_ * Config::OBJECT_ZOOM_;
    }
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    static sf::CircleShape star_shape;
    star_shape.setPosition(position_ * Config::PIXELS_PER_KM_);

    auto pixel_radius = radius_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_;
    star_shape.setRadius(pixel_radius);
    star_shape.setOrigin(pixel_radius, pixel_radius);

    star_shape.setFillColor(sf::Color(255, 255, 255, color_alpha_));

    target.draw(star_shape, states);
}