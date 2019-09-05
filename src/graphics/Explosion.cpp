//
// Created by jprolejko on 30.06.19.
//

#include <utils/Utils.h>
#include <Config.h>

#include <graphics/Explosion.h>


Explosion::Explosion(const sf::Vector2f &position, const sf::Vector2f &direction, float radius) :
        Animation("explosion" + std::to_string(utils::getRandom<int>(1, 3)),
                  {Explosion::WIDTH_PX_, Explosion::HEIGHT_PX_}, position,
                  Explosion::DURATION_S_, Explosion::MAX_FRAMES_COUNT_,
                  AnimationType::QUADRATIC) {
    float scale_factor = 20.0f;
    std::tuple<float, float> polar_direction = utils::cartesianToPolar(direction);
    float scale = scale_factor * radius * CFG.getFloat("pixels_per_km") * std::get<0>(polar_direction);
    animation_sprite_.setScale(scale_factor * radius * CFG.getFloat("pixels_per_km") / Explosion::WIDTH_PX_,
                              scale_factor * radius * CFG.getFloat("pixels_per_km") / Explosion::HEIGHT_PX_);
    animation_sprite_.setRotation(180.0f + std::get<1>(polar_direction) * 180.0f / M_PI);
}