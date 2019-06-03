//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_UTILS_H
#define GRAVITY_UTILS_H

#include <SFML/Graphics.hpp>

namespace utils {

    sf::Vector2f vectorLengthLimit(const sf::Vector2f &vector_in, float max_length);

    bool isNearlyEqual(const sf::Vector2f &a, const sf::Vector2f &b, float abs_error);

    double getDistance(const sf::Vector2f &a, const sf::Vector2f &b);

} // namespace utils

#endif //GRAVITY_UTILS_H
