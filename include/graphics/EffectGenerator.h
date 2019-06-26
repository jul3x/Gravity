//
// Created by jprolejko on 24.06.19.
//

#ifndef GRAVITY_GRAPHICS_EFFECTGENERATOR_H
#define GRAVITY_GRAPHICS_EFFECTGENERATOR_H

#include <SFML/Graphics.hpp>

#include <objects/AbstractDrawableObject.h>
#include <Config.h>

class EffectGenerator {

public:
    explicit EffectGenerator() = default;

    EffectGenerator(const EffectGenerator&) = delete;
    EffectGenerator& operator=(const EffectGenerator&) = delete;

    void initialize();

    void clear();

    void addToTexture(const AbstractDrawableObject &object);
    void addToTexture(const sf::Sprite &object);
    void renderCurrentGaussianBlur(sf::RenderTarget &target);

private:
    sf::RenderTexture texture_, texture_2_;

};


#endif // GRAVITY_GRAPHICS_EFFECTGENERATOR_H