//
// Created by jprolejko on 05.09.19.
//

#ifndef GRAVITY_GRAPHICS_SPAWNANIMATION_H
#define GRAVITY_GRAPHICS_SPAWNANIMATION_H

#include <graphics/Animation.h>
#include <system/Config.h>


class SpawnAnimation : public Animation {

public:
    SpawnAnimation() = delete;

    SpawnAnimation(const sf::Vector2f &position,
                   float radius) : Animation("spawn",
                                             {SpawnAnimation::WIDTH_PX_, SpawnAnimation::HEIGHT_PX_}, position,
                                             SpawnAnimation::DURATION_S_, SpawnAnimation::MAX_FRAMES_COUNT_) {
        float scale_factor = 10.0f;
        float scale = scale_factor * radius * CFG.getFloat("pixels_per_km");
        animation_sprite_.setScale(scale_factor * radius * CFG.getFloat("pixels_per_km") / SpawnAnimation::WIDTH_PX_,
                                   scale_factor * radius * CFG.getFloat("pixels_per_km") / SpawnAnimation::HEIGHT_PX_);
    }

private:
    static constexpr short int MAX_FRAMES_COUNT_ = 16;
    static constexpr float DURATION_S_ = 0.3f;
    static constexpr short int WIDTH_PX_ = 200;
    static constexpr short int HEIGHT_PX_ = 200;
};


#endif // GRAVITY_GRAPHICS_SPAWNANIMATION_H
