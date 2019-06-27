//
// Created by jprolejko on 06.03.19.
//

#ifndef GRAVITY_PHYSICS_PHYSICS_H
#define GRAVITY_PHYSICS_PHYSICS_H

#include <vector>
#include <list>
#include <cmath>

#include <physics/RungeKuttaSolver.h>
#include <physics/GravityEquation.h>
#include <objects/Planet.h>
#include <utils/Utils.h>
#include <Config.h>

// list planet -> list physical objects

class Physics {

public:
    explicit Physics(std::list<Planet> &planets);

    Physics(const Physics&) = delete;
    Physics& operator=(const Physics&) = delete;

    void update(float time_elapsed);

private:
    inline void handleCollisions(float time_elapsed);
    inline void applyGravitationalMovement(float time_elapsed);
    
    inline void applyMomentumConservation(Planet &first, const Planet &second);
    inline void applyDestruction(std::list<Planet>::iterator &first, std::list<Planet>::iterator &second);

    std::list<Planet> &planets_;

    GravityEquation equation_;
    RungeKuttaSolver<float, int> solver_;

};


#endif //GRAVITY_PHYSICS_PHYSICS_H
