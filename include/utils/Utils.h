//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_UTILS_UTILS_H
#define GRAVITY_UTILS_UTILS_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include <objects/Planet.h>

namespace utils {

    inline sf::Vector2f vectorLengthLimit(const sf::Vector2f &vector_in, float max_length) {
        float length = std::hypot(vector_in.x, vector_in.y);

        sf::Vector2f out = vector_in;

        if (length > max_length) {
            out.x = out.x / length * max_length;
            out.y = out.y / length * max_length;
        }

        return out;
    }

    inline bool isNearlyEqual(float a, float b, float abs_error) {
        return std::abs(a - b) < abs_error;
    }

    inline bool isNearlyEqual(const sf::Vector2f &a, const sf::Vector2f &b, float abs_error) {
        return std::abs(a.x - b.x) < abs_error && std::abs(a.y - b.y) < abs_error;
    }

    inline double getDistance(const sf::Vector2f &a, const sf::Vector2f &b) {
        return std::hypot(b.x - a.x, b.y - a.y);
    }

    inline bool isCollidable(const Planet &first, const Planet &second) {
        // circle - circle collision
        {
            double distance = utils::getDistance(first.getPosition(), second.getPosition());
            double max_distance = first.getRadius() + second.getRadius();
                
            if (distance < max_distance)
            {
                return true;
            }
        }

        return false;
    }

} // namespace utils

#endif //GRAVITY_UTILS_UTILS_H
