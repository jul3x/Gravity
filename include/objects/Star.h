//
// Created by jprolejko on 10.06.19.
//

#ifndef GRAVITY_OBJECTS_STAR_H
#define GRAVITY_OBJECTS_STAR_H

#include <objects/AbstractCelestialBody.h>

class Star : public AbstractCelestialBody {
public:
    Star() = default;

    Star(const sf::Vector2f &position, const sf::Vector2f &velocity, const float radius, const sf::Color &color);

    void update(float time_elapsed);
    
private:
    static constexpr float ALPHA_CHANGE_VELOCITY_ = 100.0f;
};


#endif // GRAVITY_OBJECTS_STAR_H

