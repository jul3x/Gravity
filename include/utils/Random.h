//
// Created by jprolejko on 13.06.19.
//

#ifndef GRAVITY_UTILS_RANDOM_H
#define GRAVITY_UTILS_RANDOM_H

#include <random>

namespace utils {

template <class T>
T getRandom(const T &left, const T &right) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution<> distribution(static_cast<double>(left), static_cast<double>(right));

    return static_cast<T>(distribution(mt));
}

} // namespace utils


#endif // GRAVITY_UTILS_RANDOM_H