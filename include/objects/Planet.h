//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_OBJECTS_PLANET_H
#define GRAVITY_OBJECTS_PLANET_H

#include <objects/AbstractCelestialBody.h>

#include <ResourceManager.h>


class Planet : public AbstractCelestialBody {

public:
    Planet() = default;

    Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius);

    void update(float time_elapsed); // TODO applyRungeKutta HERE

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        static sf::CircleShape body_shape;
        body_shape.setTexture(&ResourceManager::getInstance().getTexture("planet"));
        body_shape.setPosition(this->getPosition() * Config::PIXELS_PER_KM_);

        auto pixel_radius = this->getRadius() * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_;
        body_shape.setRadius(pixel_radius);
        body_shape.setOrigin(pixel_radius, pixel_radius);

        body_shape.setFillColor(this->getColor());

        target.draw(body_shape, states);
    }

    static sf::Texture planet_texture_;

};


#endif // GRAVITY_OBJECTS_PLANET_H
