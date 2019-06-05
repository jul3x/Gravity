//
// Created by jprolejko on 27.02.19.
//

#include <iostream>
#include <cmath>

#include <Utils.h>

namespace utils {

    sf::Vector2f vectorLengthLimit(const sf::Vector2f &vector_in, float max_length) {
        float length = std::hypot(vector_in.x, vector_in.y);

        sf::Vector2f out = vector_in;

        if (length > max_length) {
            out.x = out.x / length * max_length;
            out.y = out.y / length * max_length;
        }

        return out;
    }

    bool isNearlyEqual(const sf::Vector2f &a, const sf::Vector2f &b, float abs_error) {
        return std::fabs(a.x - b.x) < abs_error && std::fabs(a.y - b.y) < abs_error;
    }

    double getDistance(const sf::Vector2f &a, const sf::Vector2f &b) {
        return std::hypot(b.x - a.x, b.y - a.y);
    }

    bool isCollidable(const Planet &first, const Planet &second, float time_elapsed) {
        double distance = utils::getDistance(first.getPosition(), second.getPosition());
        double max_distance = first.getRadius() + second.getRadius();
            
        if (distance < max_distance)
        {
            return true;
        }

        return false;
    }

} // namespace utils
