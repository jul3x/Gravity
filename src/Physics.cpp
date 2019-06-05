//
// Created by jprolejko on 06.03.19.
//

#include <iostream>
#include <iterator>
#include <cassert>

#include <Physics.h>
#include <Utils.h>

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
            if (utils::isCollidable(*current_planet, *other_planet, time_elapsed))
            {
                move_forward = false;
                auto new_current_planet = std::next(current_planet);
            
                if (std::distance(current_planet, other_planet) == 1)
                {
                    new_current_planet = std::next(new_current_planet);
                }
                
                planets_.erase(current_planet);
                planets_.erase(other_planet);
                
                current_planet = new_current_planet;

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
    for (auto current_planet = planets_.begin(); current_planet != planets_.end(); ++current_planet)
    {
        std::vector<float> equation_vars(4);
        equation_vars.at(0) = current_planet->getPosition().x;
        equation_vars.at(1) = current_planet->getPosition().y;
        equation_vars.at(2) = current_planet->getVelocity().x;
        equation_vars.at(3) = current_planet->getVelocity().y;

        equation_vars = applyRungeKutta(equation_vars, time_elapsed, current_planet);

        current_planet->setPosition({equation_vars.at(0), equation_vars.at(1)});
        current_planet->setVelocity({equation_vars.at(2), equation_vars.at(3)});
    }
}

std::vector<float> Physics::applyGravityForceEquations(const std::vector<float> &in_values,
                                                       const std::list<Planet>::iterator &current_planet) {
    if (in_values.size() != 4)
    {
        throw std::runtime_error("Wrong size of vector of equations!");
    }

    std::vector<float> out_values(in_values.size());

    out_values.at(0) = in_values.at(2);
    out_values.at(1) = in_values.at(3);
    out_values.at(2) = 0.0;
    out_values.at(3) = 0.0;

    for (auto planet = planets_.begin(); planet != planets_.end(); ++planet)
    {
        if (planet != current_planet)
        {
            float distance = std::hypot(planet->getPosition().x - in_values.at(0),
                                        planet->getPosition().y - in_values.at(1));
            float alfa = std::atan2(planet->getPosition().y - in_values.at(1),
                                    planet->getPosition().x - in_values.at(0));

            out_values.at(2) += Config::GRAVITY_CONST * planet->getMass() / std::pow(distance, 2.0f) * std::cos(alfa);
            out_values.at(3) += Config::GRAVITY_CONST * planet->getMass() / std::pow(distance, 2.0f) * std::sin(alfa);
        }
    }

    return out_values;
}


std::vector<float> Physics::applyRungeKutta(const std::vector<float> &in_values, float step,
                                            const std::list<Planet>::iterator &current_planet) {
    auto vectors_size = in_values.size();
    std::vector<float> k1(vectors_size), k2(vectors_size), k3(vectors_size), k4(vectors_size);
    std::vector<float> temporary_vec(vectors_size), out_values(vectors_size);

    k1 = applyGravityForceEquations(in_values, current_planet);

    for (size_t i = 0; i < k1.size(); i++)
    {
        k1.at(i) = k1.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k1.at(i) / 2.0f;
    }

    k2 = applyGravityForceEquations(temporary_vec, current_planet);

    for (size_t i = 0; i < k2.size(); i++)
    {
        k2.at(i) = k2.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k2.at(i) / 2.0f;
    }

    k3 = applyGravityForceEquations(temporary_vec, current_planet);

    for (size_t i = 0; i < k3.size(); i++)
    {
        k3.at(i) = k3.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k3.at(i);
    }

    k4 = applyGravityForceEquations(temporary_vec, current_planet);

    for (auto &k : k4)
    {
        k = k * step;
    }

    for (size_t i = 0; i < out_values.size(); i++)
    {
        out_values.at(i) = in_values.at(i) + (k1.at(i) + 2.0f * k2.at(i) + 2.0f * k3.at(i) + k4.at(i)) / 6.0f;
    }

    return out_values;
}
