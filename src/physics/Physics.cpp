//
// Created by jprolejko on 06.03.19.
//

#include <Engine.h>
#include <utils/Geometry.h>

#include <physics/Physics.h>


Physics::Physics(std::list<Planet> &planets) : planets_(planets), equation_(planets_), solver_(equation_) {}

void Physics::update(float time_elapsed) {
    for (auto &planet : planets_)
    {
        planet.update(time_elapsed);
    }
    
    applyCollisions(time_elapsed);
    applyGravitationalMovement(time_elapsed);
}

inline void Physics::applyCollisions(float time_elapsed) {
    auto current_planet = planets_.begin();
    bool move_forward;

    while (current_planet != planets_.end())
    {
        move_forward = true;
        auto other_planet = std::next(current_planet);
        while (other_planet != planets_.end())
        {
            if (utils::isCollidable(*current_planet, *other_planet))
            {
                move_forward = false;

                applyDestruction(current_planet, other_planet);

                break;
            }
            else
            {
                ++other_planet;
            }
        }

        if (move_forward)
        {
            ++current_planet;
        }
    }
}

inline void Physics::applyGravitationalMovement(float time_elapsed) {
    static std::vector<float> equation_vars(4);
    
    for (auto &planet : planets_)
    {
        equation_vars = {planet.getPosition().x, planet.getPosition().y,
                         planet.getVelocity().x, planet.getVelocity().y};

        solver_.apply(equation_vars, time_elapsed, &planet);

        planet.setPosition(equation_vars.at(0), equation_vars.at(1));
        planet.setVelocity(equation_vars.at(2), equation_vars.at(3));
    }
}

inline void Physics::applyMomentumConservation(Planet &first, const Planet &second) {
    // first planet gets momentum from the second one
    sf::Vector2f velocity = first.getVelocity() +
        second.getMass() / first.getMass() * second.getVelocity();
    first.setVelocity(velocity);
}

inline void Physics::applyDestruction(std::list<Planet>::iterator &first, std::list<Planet>::iterator &second) {
    static constexpr double MASS_TOLERANCE_FACTOR = 1.5;

    auto new_first = std::next(first);

    if (first->getMass() >= second->getMass() * MASS_TOLERANCE_FACTOR)
    {
        applyMomentumConservation(*first, *second);
        Engine::getInstance().destroyPlanet(second);
        
        first = std::next(first);
    }
    else if (first->getMass() * MASS_TOLERANCE_FACTOR <= second->getMass())
    {
        applyMomentumConservation(*second, *first);
        Engine::getInstance().destroyPlanet(first);
            
        first = new_first;
    }
    else
    {        
        if (std::distance(first, second) == 1)
        {
            new_first = std::next(new_first);
        }
        
        Engine::getInstance().destroyPlanet(first);
        Engine::getInstance().destroyPlanet(second);
        
        first = new_first;
    }
}