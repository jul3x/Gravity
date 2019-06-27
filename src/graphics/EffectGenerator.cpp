//
// Created by jprolejko on 24.06.19.
//


#include <ResourceManager.h>

#include <graphics/EffectGenerator.h>

#include <Config.h>


void EffectGenerator::initialize() {
    if (!texture_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_) ||
        !texture_2_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_))
    {
        throw std::runtime_error("[EffectGenerator] Cannot create rendering texture!");
    }
}

void EffectGenerator::clear() {
    texture_.clear();
    texture_2_.clear();
}

void EffectGenerator::addToTexture(const AbstractDrawableObject &object) {
    texture_.draw(object);
}

void EffectGenerator::addToTexture(const sf::Sprite &object) {
    texture_.draw(object);
}

void EffectGenerator::renderCurrentGaussianBlur(sf::RenderTarget &target) {
    texture_.display();

    ResourceManager::getInstance().getShader("blur").setUniform(
        "texture", sf::Shader::CurrentTexture);
    ResourceManager::getInstance().getShader("blur").setUniform(
        "blur_radius", sf::Vector2f(0.4f / Config::WINDOW_WIDTH_PIXELS_, 0.0f));
    
    static sf::Sprite sprite(texture_.getTexture());

    texture_2_.draw(sprite, &ResourceManager::getInstance().getShader("blur"));
    texture_2_.display();

    static sf::Sprite sprite_2(texture_2_.getTexture());

    ResourceManager::getInstance().getShader("blur").setUniform(
        "texture", sf::Shader::CurrentTexture);
    ResourceManager::getInstance().getShader("blur").setUniform(
        "blur_radius", sf::Vector2f(0.0f, 0.4f / Config::WINDOW_HEIGHT_PIXELS_));
    target.draw(sprite_2, &ResourceManager::getInstance().getShader("blur"));
}