//
// Created by jprolejko on 26.02.19.
//

#include <SFML/Graphics/Vertex.hpp>

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
    auto pixel_radius = this->getRadius() * CFG.getFloat("pixels_per_km");

    {
        std::vector<sf::Vertex> trail_vert;

        float factor = pixel_radius / static_cast<float>(trail_.size() * trail_.size());

        if (trail_.size() >= 2)
        {
            trail_vert.emplace_back(trail_.front(), sf::Color{255, 255, 255, 100}, sf::Vector2f{});
        }

        for (size_t i = 1; i < trail_.size(); ++i)
        {
            float temp_r = factor * i * i;
            // make 2 points
            sf::Vector2f diff = trail_.at(i) - trail_.at(i - 1);
            float dir = std::atan2(diff.y, diff.x) + M_PI_2;

            sf::Vector2f norm = {std::cos(dir), std::sin(dir)};
            trail_vert.emplace_back(trail_.at(i) - temp_r * norm,
                    sf::Color{255, 255, 255, 100}, sf::Vector2f{});
            trail_vert.emplace_back(trail_.at(i) + temp_r * norm,
                    sf::Color{255, 255, 255, 100}, sf::Vector2f{});
        }

        target.draw(&trail_vert[0], trail_vert.size(), sf::TriangleStrip, states);
    }

    static sf::CircleShape body_shape;
    body_shape.setTexture(&ResourceManager::getInstance().getTexture("planet"));
    body_shape.setPosition(this->getPosition() * CFG.getFloat("pixels_per_km"));

    body_shape.setRadius(pixel_radius);
    body_shape.setOrigin(pixel_radius, pixel_radius);

    body_shape.setFillColor(this->getColor());

    target.draw(body_shape, states);
}