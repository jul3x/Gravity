//
// Created by jprolejko on 10.06.19.
//

#include <SFML/Graphics.hpp>

#include <Config.h>

class Star : public sf::Drawable {
public:
    Star() {
    }

    Star(const sf::Vector2f &position, const float radius, const float color_alpha) :
        position_(position), radius_(radius), color_alpha_(color_alpha), alfa_change_velocity_(25.0f) {
    }

    const sf::Vector2f& getPosition() const {
        return position_;
    }

    void setPosition(const sf::Vector2f &position) {
        position_ = position;
    }

    void updateAlpha(float time_elapsed) {
        if (color_alpha_ >= 100.0f || color_alpha_ <= 0.0f) 
        {
            alfa_change_velocity_ = -alfa_change_velocity_;
        }
        
        color_alpha_ += alfa_change_velocity_ * time_elapsed;
        position_ = position_ + time_elapsed * sf::Vector2f{radius_, radius_};

        // infinite loop of movement
        if ((position_.x - radius_ * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_WIDTH_PIXELS_ / 2.0f)
        {
            position_.x = -Config::WINDOW_WIDTH_PIXELS_ / 2.0f / Config::PIXELS_PER_KM_ - radius_ * Config::OBJECT_ZOOM_;
        }

        if ((position_.y - radius_ * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_HEIGHT_PIXELS_ / 2.0f)
        {
            position_.y = -Config::WINDOW_HEIGHT_PIXELS_ / 2.0f / Config::PIXELS_PER_KM_ - radius_ * Config::OBJECT_ZOOM_;
        }
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        static sf::CircleShape star_shape;
        star_shape.setPosition(position_ * Config::PIXELS_PER_KM_);

        auto pixel_radius = radius_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_;
        star_shape.setRadius(pixel_radius);
        star_shape.setOrigin(pixel_radius, pixel_radius);

        star_shape.setFillColor(sf::Color(255, 255, 255, static_cast<int>(color_alpha_)));

        target.draw(star_shape, states);
    }

    float color_alpha_;
    float alfa_change_velocity_;

    sf::Vector2f position_;
    float radius_;
};