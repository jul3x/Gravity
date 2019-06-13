//
// Created by jprolejko on 10.06.19.
//

#ifndef GRAVITY_OBJECTS_STAR_H
#define GRAVITY_OBJECTS_STAR_H

#include <SFML/Graphics.hpp>


class Star : public sf::Drawable {
public:
    Star() = default;

    Star(const sf::Vector2f &position, const sf::Vector2f &velocity, const float radius, const float color_alpha);

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f &position);

    void update(float time_elapsed);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    int color_alpha_;
    int alfa_change_velocity_;

    sf::Vector2f position_;
    sf::Vector2f velocity_;
    float radius_;
};

#endif // GRAVITY_OBJECTS_STAR_H

