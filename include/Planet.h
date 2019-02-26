//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_PLANET_H
#define GRAVITY_PLANET_H

#include <SFML/System.hpp>

class Planet {

public:
    Planet() = default;
    Planet(const sf::Vector2f &pos, const sf::Vector2f &vel, double r);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    double getRadius() const;
    double getDensity() const;

    void setPosition(const sf::Vector2f &pos);
    void setVelocity(const sf::Vector2f &vel);
private:
    sf::Vector2f pos_;
    sf::Vector2f vel_;

    double r_;

    constexpr static double DENSITY_ = 5000000;
};


#endif //GRAVITY_PLANET_H
