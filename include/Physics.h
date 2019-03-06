//
// Created by jprolejko on 06.03.19.
//

#ifndef GRAVITY_PHYSICS_H
#define GRAVITY_PHYSICS_H

#include <vector>

#include <Planet.h>

class Physics {

public:
    explicit Physics(std::vector<Planet> &planets);

    Physics(const Physics&) = delete;
    Physics& operator=(const Physics&) = delete;

    void update(float time_elapsed);

private:
    std::vector<Planet> &planets_;

};


#endif //GRAVITY_PHYSICS_H
