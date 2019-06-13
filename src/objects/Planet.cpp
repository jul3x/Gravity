//
// Created by jprolejko on 26.02.19.
//


#include <utils/Random.h>
#include <Config.h>

#include <objects/Planet.h>

Planet::Planet(const sf::Vector2f &pos_km, const sf::Vector2f &vel_km, float r_km) : pos_km_(pos_km),
                                                                                     vel_km_(vel_km),
                                                                                     r_km_(r_km) {
    // random color initialization
    color_.r = utils::getRandom<int>(0, 255);
    color_.g = utils::getRandom<int>(0, 255);
    color_.b = utils::getRandom<int>(0, 255);
}

sf::Vector2f Planet::getPosition() const {
    return pos_km_;
}

sf::Vector2f Planet::getVelocity() const {
    return vel_km_;
}

float Planet::getRadius() const {
    return r_km_;
}

float Planet::getMass() const {
    return Config::DENSITY_KG_M_ * 4.0f / 3.0f * static_cast<float>(M_PI) * std::pow(this->getRadius(), 3.0f);
}

sf::Color Planet::getColor() const {
    return color_;
}

void Planet::setPosition(const sf::Vector2f &pos_km) {
    pos_km_ = pos_km;
}

void Planet::setVelocity(const sf::Vector2f &vel_km) {
    vel_km_ = vel_km;
}