//
// Created by jprolejko on 16.06.19.
//


#ifndef GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H
#define GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H

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

    const sf::Color& getColor() const {
        return color_;
    }

protected:
    sf::Vector2f position_;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    sf::Color color_;
};

#endif // GRAVITY_OBJECTS_ABSTRACTDRAWABLEOBJECT_H
