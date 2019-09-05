//
// Created by jprolejko on 05.09.19.
//

#ifndef GRAVITY_GRAPHICS_ANIMATION_H
#define GRAVITY_GRAPHICS_ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <objects/AbstractDrawableObject.h>

#include <ResourceManager.h>


class Animation : public AbstractDrawableObject {

public:
    enum class AnimationType
    {
        LINEAR,
        QUADRATIC
    };

    Animation() = delete;

    Animation(const std::string &texture_name,
              const sf::Vector2i &frame_size,
              const sf::Vector2f &position,
              float duration_s, short int frames_count,
              const AnimationType &animation_type = AnimationType::LINEAR);

    bool update(float time_elapsed);

protected:
    short int max_frames_count_;
    float duration_s_;

    sf::Vector2i frame_size_;

    sf::IntRect animation_source_;
    sf::Sprite animation_sprite_;

    AnimationType type_;

    float time_elapsed_;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif // GRAVITY_GRAPHICS_ABSTRACTANIMATION_H
