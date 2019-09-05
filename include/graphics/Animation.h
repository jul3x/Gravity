//
// Created by jprolejko on 30.08.19.
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
              const AnimationType &animation_type = AnimationType::LINEAR) : AbstractDrawableObject(position),
                                                                             frame_size_(frame_size),
                                                                             animation_source_({0, 0}, frame_size_),
                                                                             type_(animation_type),
                                                                             duration_s_(duration_s),
                                                                             max_frames_count_(frames_count),
                                                                             time_elapsed_(0.0f) {
        animation_sprite_.setTexture(ResourceManager::getInstance().getTexture(texture_name));

        animation_sprite_.setPosition(this->getPosition());
        animation_sprite_.setOrigin(frame_size_.x / 2, frame_size_.y / 2);
    }

    bool update(float time_elapsed) {
        time_elapsed_ += time_elapsed;

        auto current_frame = static_cast<short int>(time_elapsed_ * max_frames_count_ / duration_s_);

        switch (type_)
        {
            case AnimationType::LINEAR:
            {
                animation_source_.left = frame_size_.x * current_frame;
                animation_source_.top = 0;
                break;
            }
            case AnimationType::QUADRATIC:
            {
                animation_source_.left = frame_size_.x *
                        (current_frame % static_cast<short int>(std::sqrt(max_frames_count_)));
                animation_source_.top = frame_size_.y *
                        (current_frame / static_cast<short int>(std::sqrt(max_frames_count_)));
                break;
            }
            default:
            {
                throw std::invalid_argument("[Animation] Animation type not implemented!");
            }
        }

        animation_sprite_.setTextureRect(animation_source_);

        if (current_frame > max_frames_count_)
        {
            return true;
        }

        return false;
    }

protected:
    short int max_frames_count_;
    float duration_s_;

    sf::Vector2i frame_size_;

    sf::IntRect animation_source_;
    sf::Sprite animation_sprite_;

    AnimationType type_;

    float time_elapsed_;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(animation_sprite_, states);
    }

};


#endif // GRAVITY_GRAPHICS_ABSTRACTANIMATION_H
