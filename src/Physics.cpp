//
// Created by jprolejko on 06.03.19.
//

#include <Physics.h>

Physics::Physics(std::vector<Planet> &planets) : planets_(planets) {}

void Physics::update(float time_elapsed) {
    for (auto &planet : planets_)
    {
        planet.setPosition(planet.getPosition() + planet.getVelocity() * time_elapsed);
    }
}