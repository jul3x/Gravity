//
// Created by jprolejko on 26.02.19.
//

#include <graphics/Graphics.h>

//  BIG TODO: Graphics only stores a list of AbstractDrawableObjects, as well as Physics -> AbstractPhysicalObjects

Graphics::Graphics() : settings_(0, 0, 8),
                       window_(sf::VideoMode(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_),
                                             "Gravity", sf::Style::Default, settings_),
                       user_interface_(window_) {
    auto current_view = window_.getView();
    current_view.setSize(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_);
    current_view.setCenter(Config::WINDOW_WIDTH_PIXELS_ / 2.0f, Config::WINDOW_HEIGHT_PIXELS_ / 2.0f);
    window_.setView(current_view);
    standard_view_ = current_view;

    if (!sf::Shader::isAvailable())
    {
        throw std::runtime_error("Shaders are not available!");
    }

    if (!shader_.loadFromFile("data/blur_shader.frag", sf::Shader::Fragment))
    {
        throw std::runtime_error("Shader files not found or are corrupted!");
    }

    if (!background_texture_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_))
    {
        throw std::runtime_error("Cannot create background rendering texture!");
    }

    if (!background_texture_2_.create(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_))
    {
        throw std::runtime_error("Cannot create background rendering texture!");
    }
}

const bool Graphics::isWindowOpen() const {
    return window_.isOpen();
}

void Graphics::handleEvents() {
    user_interface_.handleEvents();
}

void Graphics::clear() {
    background_texture_2_.clear();
    background_texture_.clear();
    window_.clear();
}

void Graphics::draw(const AbstractDrawableObject &object, const Graphics::EffectType &effect) {
    // will be changed next time, don't worry
    if (effect == Graphics::EffectType::NONE)
    {
        window_.draw(object);
    }
    else if (effect == Graphics::EffectType::GAUSSIAN_BLUR)
    {
        auto current_view = window_.getView();
        window_.setView(standard_view_);

        // drawing uses the same functions

        background_texture_.draw(object); // or any other drawable
        background_texture_.display();

        shader_.setUniform("texture", sf::Shader::CurrentTexture);
        shader_.setUniform("blur_radius", sf::Vector2f(0.5f / Config::WINDOW_WIDTH_PIXELS_, 0.0f));
        // draw it to the window
        static sf::Sprite sprite(background_texture_.getTexture());

        background_texture_2_.display();
        background_texture_2_.draw(sprite, &shader_);
        static sf::Sprite sprite2(background_texture_2_.getTexture());
        shader_.setUniform("texture", sf::Shader::CurrentTexture);
        shader_.setUniform("blur_radius", sf::Vector2f(0.0f, 0.5f / Config::WINDOW_HEIGHT_PIXELS_));
        window_.draw(sprite2, &shader_);

        window_.setView(current_view);
    }
}


void Graphics::display() {
    user_interface_.draw();

    window_.display();
}