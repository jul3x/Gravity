//
// Created by jprolejko on 06.03.19.
//

#ifndef GRAVITY_PHYSICS_H
#define GRAVITY_PHYSICS_H

#include <vector>
#include <list>
#include <cmath>

#include <Utils.h>
#include <Config.h>
#include <Planet.h>


class Physics {

public:
    explicit Physics(std::list<Planet> &planets);

    Physics(const Physics&) = delete;
    Physics& operator=(const Physics&) = delete;

    void update(float time_elapsed);

private:
    inline void handleCollisions(float time_elapsed);
    inline void handleMovement(float time_elapsed);
    
    inline std::vector<float> applyRungeKutta(const std::vector<float> &in_values, float step,
                                              const std::list<Planet>::iterator &current_planet);
    inline std::vector<float> applyGravityForceEquations(const std::vector<float> &in_values,
                                                         const std::list<Planet>::iterator &current_planet);

    std::list<Planet> &planets_;

};


#endif //GRAVITY_PHYSICS_H
