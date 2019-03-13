//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_PLANET_H
#define GRAVITY_PLANET_H

#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>

class Planet {

public:
    Planet() = default;
    Planet(const sf::Vector2f &pos_km, const sf::Vector2f &vel_km, float r_km);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    float getRadius() const;

    sf::Color getColor() const;

    void setPosition(const sf::Vector2f &pos_km);
    void setVelocity(const sf::Vector2f &vel_km);

private:
    sf::Vector2f pos_km_;
    sf::Vector2f vel_km_;

    float r_km_;

    sf::Color color_;
};


#endif //GRAVITY_PLANET_H
