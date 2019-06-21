//
// Created by jprolejko on 16.06.19.
//


#ifndef GRAVITY_OBJECTS_ABSTRACTPHYSICALOBJECT_H
#define GRAVITY_OBJECTS_ABSTRACTPHYSICALOBJECT_H

#include <objects/AbstractDrawableObject.h>


class AbstractPhysicalObject : public AbstractDrawableObject {
public:
    AbstractPhysicalObject() = default;

    AbstractPhysicalObject(const AbstractDrawableObject &object, const sf::Vector2f &velocity) : 
        AbstractDrawableObject(object), velocity_(velocity) {}

    AbstractPhysicalObject(const sf::Vector2f &position, const sf::Vector2f &velocity) : 
        AbstractDrawableObject(position), velocity_(velocity) {}
    
    AbstractPhysicalObject(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Color color) : 
        AbstractDrawableObject(position, color), velocity_(velocity) {}

    const sf::Vector2f& getVelocity() const {
        return velocity_;
    }

    void setVelocity(const sf::Vector2f &velocity) {
        velocity_ = velocity;
    }

    void setVelocity(const float x, const float y) {
        velocity_.x = x;
        velocity_.y = y;
    }

    virtual float getMass() const = 0;

    virtual void update(float time_elapsed) = 0;

protected:
    sf::Vector2f velocity_;

};

#endif // GRAVITY_OBJECTS_ABSTRACTPHYSICALOBJECT_H
