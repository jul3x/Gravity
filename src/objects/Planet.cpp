//
// Created by jprolejko on 26.02.19.
//

#include <objects/Planet.h>


Planet::Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius) : 
    AbstractCelestialBody(position, velocity, radius) {}

void Planet::update(float time_elapsed) {
    // TODO APPLY RUNGE KUTTA SOLVING
}