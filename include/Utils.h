//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_UTILS_H
#define GRAVITY_UTILS_H

#include <SFML/Graphics.hpp>

namespace utils {

    sf::Vector2f vectorLengthLimit(const sf::Vector2f &vector_in, float max_length);

} // namespace utils

#endif //GRAVITY_UTILS_H