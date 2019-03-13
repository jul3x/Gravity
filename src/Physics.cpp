//
// Created by jprolejko on 06.03.19.
//

#include <iostream>
#include <cassert>

#include <Physics.h>

Physics::Physics(std::vector<Planet> &planets) : planets_(planets) {}

void Physics::update(float time_elapsed) {
    for (auto planet = planets_.begin(); planet != planets_.end(); ++planet)
    {
        std::vector<float> equation_vars(4);
        equation_vars.at(0) = planet->getPosition().x;
        equation_vars.at(1) = planet->getPosition().y;
        equation_vars.at(2) = planet->getVelocity().x;
        equation_vars.at(3) = planet->getVelocity().y;

        equation_vars = applyRungeKutta(equation_vars, time_elapsed,
                                        static_cast<unsigned int>(std::distance(planets_.begin(), planet)));

        planet->setPosition({equation_vars.at(0), equation_vars.at(1)});
        planet->setVelocity({equation_vars.at(2), equation_vars.at(3)});
    }
}

std::vector<float> Physics::applyGravityForceEquations(const std::vector<float> &in_values,
                                                       unsigned int planet_number) {
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
        // check if it is not the same planet
        if (std::distance(planets_.begin(), planet) != planet_number)
        {
            float distance = std::hypot(planet->getPosition().x - in_values.at(0),
                                        planet->getPosition().y - in_values.at(1));
            float alfa = std::atan2(planet->getPosition().y - in_values.at(1),
                                    planet->getPosition().x - in_values.at(0));

            float mass = Config::DENSITY_KG_M_ *
                    4.0f / 3.0f * static_cast<float>(M_PI) * std::pow(planet->getRadius(), 3.0f);

            out_values.at(2) += Config::GRAVITY_CONST * mass / std::pow(distance, 2.0f) * std::cos(alfa);
            out_values.at(3) += Config::GRAVITY_CONST * mass / std::pow(distance, 2.0f) * std::sin(alfa);
        }
    }

    return out_values;
}


std::vector<float> Physics::applyRungeKutta(const std::vector<float> &in_values, float step,
                                            unsigned int planet_number) {
    auto vectors_size = in_values.size();
    std::vector<float> k1(vectors_size), k2(vectors_size), k3(vectors_size), k4(vectors_size);
    std::vector<float> temporary_vec(vectors_size), out_values(vectors_size);

    // TEST
    //     k1 = applyGravityForceEquations(in_values);
    //    for (size_t i = 0; i < out_values.size(); i++)
    //    {
    //        out_values.at(i) = in_values.at(i) + k1.at(i) * step;
    //    }
    //    return out_values;

    k1 = applyGravityForceEquations(in_values, planet_number);

    for (size_t i = 0; i < k1.size(); i++)
    {
        k1.at(i) = k1.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k1.at(i) / 2.0f;
    }

    k2 = applyGravityForceEquations(temporary_vec, planet_number);

    for (size_t i = 0; i < k2.size(); i++)
    {
        k2.at(i) = k2.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k2.at(i) / 2.0f;
    }

    k3 = applyGravityForceEquations(temporary_vec, planet_number);

    for (size_t i = 0; i < k3.size(); i++)
    {
        k3.at(i) = k3.at(i) * step;
        temporary_vec.at(i) = in_values.at(i) + k3.at(i);
    }

    k4 = applyGravityForceEquations(temporary_vec, planet_number);

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
