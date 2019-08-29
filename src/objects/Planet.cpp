//
// Created by jprolejko on 26.02.19.
//

#include <objects/Planet.h>

Planet::Planet(const sf::Vector2f &position, const sf::Vector2f &velocity, float radius) : 
    AbstractCelestialBody(position, velocity, radius) {}

void Planet::update(float time_elapsed) {
    trail_.push_back(this->getPosition());

    if (trail_.size() > Planet::TRAIL_COUNT_)
    {
        trail_.pop_front();
    }
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    {
        static sf::RectangleShape trail_shape;
        trail_shape.setFillColor(sf::Color::White);
        trail_shape.setSize({5.0f, 5.0f});
        trail_shape.setOrigin(2.5f, 2.5f);

        for (const auto &trail_point : trail_)
        {
            trail_shape.setPosition(trail_point);
            target.draw(trail_shape, states);
        }
    }

    static sf::CircleShape body_shape;
    body_shape.setTexture(&ResourceManager::getInstance().getTexture("planet"));
    body_shape.setPosition(this->getPosition() * CFG.getFloat("pixels_per_km"));

    auto pixel_radius = this->getRadius() * CFG.getFloat("pixels_per_km");
    body_shape.setRadius(pixel_radius);
    body_shape.setOrigin(pixel_radius, pixel_radius);

    body_shape.setFillColor(this->getColor());

    target.draw(body_shape, states);
}