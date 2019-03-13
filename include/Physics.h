//
// Created by jprolejko on 06.03.19.
//

#ifndef GRAVITY_PHYSICS_H
#define GRAVITY_PHYSICS_H

#include <vector>
#include <cmath>

#include <Utils.h>
#include <Config.h>
#include <Planet.h>


class Physics {

public:
    explicit Physics(std::vector<Planet> &planets);

    Physics(const Physics&) = delete;
    Physics& operator=(const Physics&) = delete;

    void update(float time_elapsed);

private:
    std::vector<float> applyRungeKutta(const std::vector<float> &in_values, float step, unsigned int planet_number);
    std::vector<float> applyGravityForceEquations(const std::vector<float> &in_values, unsigned int planet_number);

    std::vector<Planet> &planets_;

};


#endif //GRAVITY_PHYSICS_H
