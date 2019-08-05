//
// Created by jprolejko on 27.06.19.
//

#ifndef GRAVITY_PHYSICS_GRAVITYEQUATION_H
#define GRAVITY_PHYSICS_GRAVITYEQUATION_H

#include <physics/RungeKuttaSolver.h>
#include <objects/Planet.h>
#include <utils/Geometry.h>
#include <Config.h>

class GravityEquation : public IEquation<float, Planet*> {

public:
    GravityEquation(const std::list<Planet> &planets) : planets_(planets) {
        size_ = 4;
    }
    
    virtual std::vector<float> operator()(const std::vector<float> &values, 
                                          const EquationParameters<Planet*> &parameters) {
        static std::vector<float> out_values(this->getSize());
        static float distance = 0.0f;
        static float theta_rad = 0.0f;
        
        if (parameters.get().size() != 1) 
        {
            throw std::invalid_argument("[GravityEquation] Wrong number of objects "
                                        "in parameters vector");
        }

        auto planet_addr = parameters.get().front();
        out_values.at(0) = values.at(2);
        out_values.at(1) = values.at(3);
        out_values.at(2) = 0.0;
        out_values.at(3) = 0.0;

        for (const auto &planet : planets_)
        {
            if (&planet != planet_addr)
            {
                std::tie(distance, theta_rad) =
                    utils::cartesianToPolar(planet.getPosition() - sf::Vector2f{values.at(0), values.at(1)});

                out_values.at(2) += Config::getInstance().GRAVITY_CONST_ * planet.getMass() /
                                    std::pow(distance, 2.0f) * std::cos(theta_rad);
                out_values.at(3) += Config::getInstance().GRAVITY_CONST_ * planet.getMass() /
                                    std::pow(distance, 2.0f) * std::sin(theta_rad);
            }
        }
        
        return out_values;
    }

private:
    const std::list<Planet> &planets_;

};

#endif // GRAVITY_PHYSICS_GRAVITYEQUATION_H