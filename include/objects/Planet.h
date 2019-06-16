//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_OBJECTS_PLANET_H
#define GRAVITY_OBJECTS_PLANET_H

#include <objects/AbstractCelestialBody.h>


class Planet : public AbstractCelestialBody {

public:
    Planet() = default;

    Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius);

    void setPosition(const sf::Vector2f &position); // TODO applyRungeKutta HERE AND ERASE THOSE METHODS
    void setVelocity(const sf::Vector2f &velocity); // TODO applyRungeKutta HERE AND ERASE THOSE METHODS

    void update(float time_elapsed); // TODO applyRungeKutta HERE
};


#endif // GRAVITY_OBJECTS_PLANET_H
