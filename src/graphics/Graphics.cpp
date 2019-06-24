//
// Created by jprolejko on 26.02.19.
//

#include <graphics/Graphics.h>


Graphics::Graphics() : settings_(0, 0, 8),
                       window_(sf::VideoMode(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_),
                                             "Gravity", sf::Style::Default, settings_),
                       user_interface_(window_) {
    current_view_ = window_.getView();
    current_view_.setSize(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_);
    current_view_.setCenter(Config::WINDOW_WIDTH_PIXELS_ / 2.0f, Config::WINDOW_HEIGHT_PIXELS_ / 2.0f);
    window_.setView(current_view_);
    standard_view_ = current_view_;

    effect_generator_.initialize();
}

const bool Graphics::isWindowOpen() const {
    return window_.isOpen();
}

void Graphics::handleEvents() {
    user_interface_.handleEvents();
}

void Graphics::setStaticView() {
    current_view_ = window_.getView();
    window_.setView(standard_view_);
}

void Graphics::setDynamicView() {
    window_.setView(current_view_);
}

void Graphics::clear() {
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
        // drawing uses the same functions
        effect_generator_.clear();
        effect_generator_.addToTexture(object);
        effect_generator_.renderCurrentGaussianBlur(window_);
    }
}


void Graphics::display() {
    user_interface_.draw();

    window_.display();
}