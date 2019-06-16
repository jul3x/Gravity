//
// Created by jprolejko on 26.02.19.
//

#include <objects/Planet.h>


Planet::Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius) : 
    AbstractCelestialBody(position, velocity, radius) {}

void Planet::setPosition(const sf::Vector2f &position) {
    position_ = position;
}

void Planet::setVelocity(const sf::Vector2f &velocity) {
    velocity_ = velocity;
}

void Planet::update(float time_elapsed) {
    // TODO APPLY RUNGE KUTTA SOLVING
}