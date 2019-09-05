//
// Created by jprolejko on 30.08.19.
//

#ifndef GRAVITY_GRAPHICS_EXPLOSION_H
#define GRAVITY_GRAPHICS_EXPLOSION_H

#include <graphics/Animation.h>


class Explosion : public Animation {

public:
    Explosion() = delete;

    Explosion(const sf::Vector2f &position,
              const sf::Vector2f &velocity,
              float radius);

private:
    static constexpr short int MAX_FRAMES_COUNT_ = 64;
    static constexpr float DURATION_S_ = 1.0f;
    static constexpr short int WIDTH_PX_ = 512;
    static constexpr short int HEIGHT_PX_ = 512;
};


#endif // GRAVITY_GRAPHICS_EXPLOSION_H
