//
// Created by jprolejko on 24.06.19.
//

#include <graphics/EffectGenerator.h>


void EffectGenerator::initialize() {
    if (!sf::Shader::isAvailable())
    {
        throw std::runtime_error("Shaders are not available!");
    }

    if (!shader_.loadFromFile("data/blur_shader.frag", sf::Shader::Fragment))
    {
        throw std::runtime_error("Shader files not found or are corrupted!");
    }

    if (!texture_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_))
    {
        throw std::runtime_error("Cannot create background rendering texture!");
    }

    if (!texture_2_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_))
    {
        throw std::runtime_error("Cannot create background rendering texture!");
    }
}

void EffectGenerator::clear() {
    texture_.clear();
    texture_2_.clear();
}

void EffectGenerator::addToTexture(const AbstractDrawableObject &object) {
    texture_.draw(object);
}

void EffectGenerator::renderCurrentGaussianBlur(sf::RenderTarget &target) {
    texture_.display();

    shader_.setUniform("texture", sf::Shader::CurrentTexture);
    shader_.setUniform("blur_radius", sf::Vector2f(0.5f / Config::WINDOW_WIDTH_PIXELS_, 0.0f));
    
    static sf::Sprite sprite(texture_.getTexture());

    texture_2_.draw(sprite, &shader_);
    texture_2_.display();

    static sf::Sprite sprite2(texture_2_.getTexture());

    shader_.setUniform("texture", sf::Shader::CurrentTexture);
    shader_.setUniform("blur_radius", sf::Vector2f(0.0f, 0.5f / Config::WINDOW_HEIGHT_PIXELS_));
    target.draw(sprite2, &shader_);
}