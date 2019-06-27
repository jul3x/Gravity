//
// Created by jprolejko on 27.06.19.
//

#ifndef GRAVITY_PHYSICS_GRAVITYEQUATION_H
#define GRAVITY_PHYSICS_GRAVITYEQUATION_H

#include <physics/RungeKuttaSolver.h>
#include <objects/Planet.h>
#include <utils/Utils.h>
#include <Config.h>

#include <iostream>

class GravityEquation : public IEquation<float, int> {

public:
    GravityEquation(const std::list<Planet> &planets) : planets_(planets) {
        size_ = 4;
    }
    
    virtual std::vector<float> operator()(const std::vector<float> &values, 
                                          const EquationParameters<int> &parameters) {
        static std::vector<float> out_values(this->getSize());
        
        if (parameters.get().size() != 1) 
        {
            throw std::invalid_argument("[GravityEquation] Wrong number of objects "
                                        "in parameters vector");
        }

        auto planet_id = parameters.get().front();
        out_values.at(0) = values.at(2);
        out_values.at(1) = values.at(3);
        out_values.at(2) = 0.0;
        out_values.at(3) = 0.0;

        for (const auto &planet : planets_)
        {
            if (planet.getId() != planet_id)
            {
                float distance = utils::getDistance(planet.getPosition(), {values.at(0), values.at(1)});
                float alfa = std::atan2(planet.getPosition().y - values.at(1),
                                        planet.getPosition().x - values.at(0));

                out_values.at(2) += Config::GRAVITY_CONST * planet.getMass() / std::pow(distance, 2.0f) * std::cos(alfa);
                out_values.at(3) += Config::GRAVITY_CONST * planet.getMass() / std::pow(distance, 2.0f) * std::sin(alfa);
            }
        }
        
        return out_values;
    }

private:
    const std::list<Planet> &planets_;

};

#endif // GRAVITY_PHYSICS_GRAVITYEQUATION_H