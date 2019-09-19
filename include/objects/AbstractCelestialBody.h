//
// Created by jprolejko on 16.06.19.
//

#ifndef GRAVITY_OBJECTS_ABSTRACTCELESTIALBODY_H
#define GRAVITY_OBJECTS_ABSTRACTCELESTIALBODY_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <objects/AbstractPhysicalObject.h>

#include <system/Config.h>


class AbstractCelestialBody : public AbstractPhysicalObject {
public:
    AbstractCelestialBody() = default;

    AbstractCelestialBody(const AbstractPhysicalObject &object,
                          float radius) : 
        AbstractPhysicalObject(object), radius_(radius) {}

    AbstractCelestialBody(const sf::Vector2f &position,
                          const sf::Vector2f &velocity,
                          float radius) : 
        AbstractPhysicalObject(position, velocity), radius_(radius) {}

    AbstractCelestialBody(const sf::Vector2f &position,
                          const sf::Vector2f &velocity,
                          float radius,
                          const sf::Color &color) : 
        AbstractPhysicalObject(position, velocity, color), radius_(radius) {}

    const float getRadius() const {
        return radius_;
    }

    float getMass() const {
        return CFG.getFloat("density_kg_m") * 4.0f / 3.0f * static_cast<float>(M_PI) * std::pow(this->getRadius(), 3.0f);
    }

    void update(float time_elapsed) = 0;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        static sf::CircleShape body_shape;
        body_shape.setPosition(this->getPosition() * CFG.getFloat("pixels_per_km"));

        auto pixel_radius = this->getRadius() * CFG.getFloat("pixels_per_km");
        body_shape.setRadius(pixel_radius);
        body_shape.setOrigin(pixel_radius, pixel_radius);

        body_shape.setFillColor(this->getColor());

        target.draw(body_shape, states);
    }

    float radius_;

};

#endif //GRAVITY_OBJECTS_ABSTRACTCELESTIALBODY_H
