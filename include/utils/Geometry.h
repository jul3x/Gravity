//
// Created by jprolejko on 27.06.19.
//

#ifndef GRAVITY_UTILS_GEOMETRY_H
#define GRAVITY_UTILS_GEOMETRY_H

#include <cmath>

#include <SFML/System/Vector2.hpp>

#include <objects/Planet.h>

namespace utils {

inline float getDistance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}

inline sf::Vector2f polarToCartesian(float r, float theta_rad) {
    if (r < 0.0f)
    {
        throw std::invalid_argument("[Utils::polarToCartesian] Radius cannot be negative!");
    }

    return {r * std::cos(theta_rad), r * std::sin(theta_rad)}; 
}

inline std::tuple<float, float> cartesianToPolar(const sf::Vector2f &vector) {
    float r = std::hypot(vector.x, vector.y);
    float theta_rad = std::atan2(vector.y, vector.x);

    return std::make_tuple(r, theta_rad);
}

inline sf::Vector2f vectorLengthLimit(const sf::Vector2f &vector_in, float max_length) {
    if (max_length < 0.0f)
    {
        throw std::invalid_argument("[utils::vectorLengthLimit] max_length cannot be negative!");
    }

    float length = std::hypot(vector_in.x, vector_in.y);

    sf::Vector2f out = vector_in;

    if (length > max_length) {
        out.x = out.x / length * max_length;
        out.y = out.y / length * max_length;
    }

    return out;
}

inline bool isCollidable(const Planet &first, const Planet &second) {
    // circle - circle collision
    {
        float distance = utils::getDistance(first.getPosition(), second.getPosition());
        float max_distance = first.getRadius() + second.getRadius();
            
        if (distance < max_distance)
        {
            return true;
        }
    }

    return false;
}

} // namespace utils

#endif // GRAVITY_UTILS_GEOMETRY_H