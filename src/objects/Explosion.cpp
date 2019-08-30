//
// Created by jprolejko on 30.06.19.
//

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <objects/Explosion.h>


Explosion::Explosion(const sf::Vector2f &position, const sf::Vector2f &direction, float radius) : 
        AbstractDrawableObject(position),
        direction_(direction),
        radius_(radius),
        current_frame_(0) {}

void Explosion::update(float time_elapsed) {
    ++current_frame_;

    if (current_frame_ > Explosion::MAX_FRAMES_COUNT_)
    {
        current_frame_ = 0;
    }
}

void Explosion::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    static sf::IntRect animation_source(0, 0, 512, 512);
    static sf::Sprite animation_sprite(ResourceManager::getInstance().getTexture("explosion"));

    animation_source.left = 512 *
            (current_frame_ % static_cast<int>(std::sqrt(Explosion::MAX_FRAMES_COUNT_)));
    animation_source.top = 512 *
            (current_frame_ / static_cast<int>(std::sqrt(Explosion::MAX_FRAMES_COUNT_)));

    animation_sprite.setTextureRect(animation_source);
    animation_sprite.setPosition(this->getPosition());
    animation_sprite.setOrigin(256, 256);

    target.draw(animation_sprite, states);
}