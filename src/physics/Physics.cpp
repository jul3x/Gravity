//
// Created by jprolejko on 06.03.19.
//

#include <iostream>
#include <iterator>
#include <cassert>

#include <physics/Physics.h>
#include <utils/Utils.h>

Physics::Physics(std::list<Planet> &planets) : planets_(planets) {}

void Physics::update(float time_elapsed) {
    handleCollisions(time_elapsed);
    handleMovement(time_elapsed);
}

void Physics::handleCollisions(float time_elapsed) {
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

void Physics::handleMovement(float time_elapsed) {
    static std::vector<float> equation_vars(4);
    
    for (auto current_planet = planets_.begin(); current_planet != planets_.end(); ++current_planet)
    {
        equation_vars = {current_planet->getPosition().x, current_planet->getPosition().y,
                         current_planet->getVelocity().x, current_planet->getVelocity().y};

        applyRungeKutta(equation_vars, time_elapsed, current_planet);

        current_planet->setPosition(equation_vars.at(0), equation_vars.at(1));
        current_planet->setVelocity(equation_vars.at(2), equation_vars.at(3));
    }
}

std::vector<float> Physics::applyGravityForceEquations(const std::vector<float> &in_values,
                                                       const std::list<Planet>::iterator &current_planet) {
    if (in_values.size() != 4)
    {
        throw std::runtime_error("Wrong size of vector of equations!");
    }

    static std::vector<float> out_values(in_values.size());

    out_values.at(0) = in_values.at(2);
    out_values.at(1) = in_values.at(3);
    out_values.at(2) = 0.0;
    out_values.at(3) = 0.0;

    for (auto planet = planets_.begin(); planet != planets_.end(); ++planet)
    {
        if (planet != current_planet)
        {
            float distance = utils::getDistance(planet->getPosition(), {in_values.at(0), in_values.at(1)});
            float alfa = std::atan2(planet->getPosition().y - in_values.at(1),
                                    planet->getPosition().x - in_values.at(0));

            out_values.at(2) += Config::GRAVITY_CONST * planet->getMass() / std::pow(distance, 2.0f) * std::cos(alfa);
            out_values.at(3) += Config::GRAVITY_CONST * planet->getMass() / std::pow(distance, 2.0f) * std::sin(alfa);
        }
    }

    return out_values;
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
        planets_.erase(second);
        
        first = std::next(first);
    }
    else if (first->getMass() * MASS_TOLERANCE_FACTOR <= second->getMass())
    {
        applyMomentumConservation(*first, *second);
        planets_.erase(first);
            
        first = new_first;
    }
    else
    {        
        if (std::distance(first, second) == 1)
        {
            new_first = std::next(new_first);
        }
        
        planets_.erase(first);
        planets_.erase(second);
        
        first = new_first;
    }
}

void Physics::applyRungeKutta(std::vector<float> &values, float step,
                              const std::list<Planet>::iterator &current_planet) {
    if (values.empty())
    {
        throw std::runtime_error("Values vector in applyRungeKutta function cannot be empty");
    }
                            
    auto vectors_size = values.size();
    static std::vector<float> k1(vectors_size), k2(vectors_size), k3(vectors_size), k4(vectors_size);
    static std::vector<float> temporary_vec(vectors_size);

    k1 = applyGravityForceEquations(values, current_planet);

    for (size_t i = 0; i < k1.size(); ++i)
    {
        k1.at(i) = k1.at(i) * step;
        temporary_vec.at(i) = values.at(i) + k1.at(i) / 2.0f;
    }

    k2 = applyGravityForceEquations(temporary_vec, current_planet);

    for (size_t i = 0; i < k2.size(); ++i)
    {
        k2.at(i) = k2.at(i) * step;
        temporary_vec.at(i) = values.at(i) + k2.at(i) / 2.0f;
    }

    k3 = applyGravityForceEquations(temporary_vec, current_planet);

    for (size_t i = 0; i < k3.size(); ++i)
    {
        k3.at(i) = k3.at(i) * step;
        temporary_vec.at(i) = values.at(i) + k3.at(i);
    }

    k4 = applyGravityForceEquations(temporary_vec, current_planet);

    for (auto &k : k4)
    {
        k = k * step;
    }

    for (size_t i = 0; i < values.size(); ++i)
    {
        values.at(i) = values.at(i) + (k1.at(i) + 2.0f * k2.at(i) + 2.0f * k3.at(i) + k4.at(i)) / 6.0f;
    }
}
