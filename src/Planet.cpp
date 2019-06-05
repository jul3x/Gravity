//
// Created by jprolejko on 26.02.19.
//

#include <random>

#include <Planet.h>
#include <Config.h>

Planet::Planet(const sf::Vector2f &pos_km, const sf::Vector2f &vel_km, float r_km) : pos_km_(pos_km),
                                                                                     vel_km_(vel_km),
                                                                                     r_km_(r_km) {
    // random color initialization
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, 255.0f);

    color_.r = static_cast<int>(dist(mt));
    color_.g = static_cast<int>(dist(mt));
    color_.b = static_cast<int>(dist(mt));
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