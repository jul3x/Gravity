//
// Created by jprolejko on 30.08.19.
//

#ifndef GRAVITY_OBJECTS_EXPLOSION_H
#define GRAVITY_OBJECTS_EXPLOSION_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <objects/AbstractDrawableObject.h>

#include <ResourceManager.h>


class Explosion : public AbstractDrawableObject {

public:
    Explosion() = default;

    Explosion(const sf::Vector2f &position,
              const sf::Vector2f &velocity,
              float radius);

    bool update(float time_elapsed);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    static constexpr short int MAX_FRAMES_COUNT_ = 64;
    static constexpr short int WIDTH_ = 512;
    static constexpr short int HEIGHT_ = 512;

    sf::IntRect animation_source_;
    sf::Sprite animation_sprite_;
    
    sf::Vector2f direction_;
    float radius_;
    short int current_frame_;
};


#endif // GRAVITY_OBJECTS_EXPLOSION_H
