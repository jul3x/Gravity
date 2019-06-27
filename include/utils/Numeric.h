//
// Created by jprolejko on 13.06.19.
//

#ifndef GRAVITY_UTILS_NUMERIC_H
#define GRAVITY_UTILS_NUMERIC_H

#include <random>
#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace utils {

template <class T>
T getRandom(const T &left, const T &right) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution<> distribution(static_cast<double>(left), static_cast<double>(right));

    return static_cast<T>(distribution(mt));
}

inline bool isNearlyEqual(float a, float b, float abs_error) {
    return std::abs(a - b) < abs_error;
}

inline bool isNearlyEqual(const sf::Vector2f &a, const sf::Vector2f &b, float abs_error) {
    return std::abs(a.x - b.x) < abs_error && std::abs(a.y - b.y) < abs_error;
}

} // namespace utils


#endif // GRAVITY_UTILS_NUMERIC_H