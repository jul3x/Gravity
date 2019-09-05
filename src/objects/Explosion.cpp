//
// Created by jprolejko on 30.06.19.
//

#include <utils/Utils.h>
#include <Config.h>

#include <objects/Explosion.h>


Explosion::Explosion(const sf::Vector2f &position, const sf::Vector2f &direction, float radius) : 
        AbstractDrawableObject(position),
        direction_(direction),
        radius_(radius),
        time_elapsed_(0.0f),
        current_frame_(0),
        animation_source_(0, 0, Explosion::WIDTH_PX_, Explosion::HEIGHT_PX_),
        animation_sprite_() {
    static short int EXPLOSION_TYPE = 0;
    int number = EXPLOSION_TYPE % 3 + 1;
    ++EXPLOSION_TYPE;
    animation_sprite_.setTexture(
            ResourceManager::getInstance().getTexture("explosion" + std::to_string(number)));

    animation_sprite_.setPosition(this->getPosition());

    float scale_factor = 20.0f;
    std::tuple<float, float> polar_direction = utils::cartesianToPolar(direction_);
    float scale = scale_factor * radius_ * CFG.getFloat("pixels_per_km") * std::get<0>(polar_direction);
    animation_sprite_.setScale(scale_factor * radius_ * CFG.getFloat("pixels_per_km") / Explosion::WIDTH_PX_,
                              scale_factor * radius_ * CFG.getFloat("pixels_per_km") / Explosion::HEIGHT_PX_);
    animation_sprite_.setRotation(180.0f + std::get<1>(polar_direction) * 180.0f / M_PI);

    animation_sprite_.setOrigin(Explosion::WIDTH_PX_ / 2, Explosion::HEIGHT_PX_ / 2);
}

bool Explosion::update(float time_elapsed) {
    time_elapsed_ += time_elapsed;

    current_frame_ = time_elapsed_ * Explosion::MAX_FRAMES_COUNT_ / Explosion::DURATION_S_;

    animation_source_.left = Explosion::WIDTH_PX_ *
            (current_frame_ % static_cast<int>(std::sqrt(Explosion::MAX_FRAMES_COUNT_)));
    animation_source_.top = Explosion::HEIGHT_PX_ *
            (current_frame_ / static_cast<int>(std::sqrt(Explosion::MAX_FRAMES_COUNT_)));

    animation_sprite_.setTextureRect(animation_source_);

    if (current_frame_ > Explosion::MAX_FRAMES_COUNT_)
    {
        return true;
    }

    return false;
}

void Explosion::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation_sprite_, states);
}