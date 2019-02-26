//
// Created by jprolejko on 26.02.19.
//

#include <Planet.h>

Planet::Planet(const sf::Vector2f &pos, const sf::Vector2f &vel, double r) : pos_(pos), vel_(vel), r_(r) {}

sf::Vector2f Planet::getPosition() const {
    return pos_;
}

sf::Vector2f Planet::getVelocity() const {
    return vel_;
}

double Planet::getRadius() const {
    return r_;
}

double Planet::getDensity() const {
    return DENSITY_;
}

void Planet::setPosition(const sf::Vector2f &pos) {
    pos_ = pos;
}

void Planet::setVelocity(const sf::Vector2f &vel) {
    vel_ = vel;
}