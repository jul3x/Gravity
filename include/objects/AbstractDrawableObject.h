//
// Created by jprolejko on 16.06.19.
//


#ifndef GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H
#define GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H

#include <cmath>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>

#include <utils/Random.h>

class AbstractDrawableObject : public sf::Drawable {
public:
    AbstractDrawableObject() = default;

    AbstractDrawableObject(const sf::Vector2f &position, const sf::Color color) : 
        position_(position), color_(color) {}

    AbstractDrawableObject(const sf::Vector2f &position) : 
        position_(position), color_(utils::getRandom<int>(0, 255), utils::getRandom<int>(0, 255), utils::getRandom<int>(0, 255)) {}

    const sf::Vector2f& getPosition() const {
        return position_;
    }

    void setPosition(const sf::Vector2f &position) {
        position_ = position;
    }

    void setPosition(const float x, const float y) {
        position_.x = x;
        position_.y = y;
    }

    const sf::Color& getColor() const {
        return color_;
    }

    void setColor(const sf::Color &color) {
        color_ = color;
    }

    int getTransparency() const {
        return color_.a;
    }

    void setTransparency(const int transparency) {
        color_.a = std::max(std::min(255, transparency), 0);
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    sf::Color color_;
    sf::Vector2f position_;
};

#endif // GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H
