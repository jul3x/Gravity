//
// Created by jprolejko on 26.02.19.
//

#include <objects/Planet.h>

#include <utils/Random.h>

Planet::Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius) : 
    AbstractCelestialBody(position, velocity, radius) {
    id_ = utils::getRandom<int>(1, 1000000); // IMPORTANT TO CHANGE!!
}

void Planet::update(float time_elapsed) {
    // TODO APPLY RUNGE KUTTA SOLVING
}

int Planet::getId() const {
    return id_;
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::CircleShape body_shape;
    body_shape.setTexture(&ResourceManager::getInstance().getTexture("planet"));
    body_shape.setPosition(this->getPosition() * Config::PIXELS_PER_KM_);

    auto pixel_radius = this->getRadius() * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_;
    body_shape.setRadius(pixel_radius);
    body_shape.setOrigin(pixel_radius, pixel_radius);

    body_shape.setFillColor(this->getColor());

    target.draw(body_shape, states);
}