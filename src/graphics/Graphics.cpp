//
// Created by jprolejko on 26.02.19.
//

#include <graphics/Graphics.h>


Graphics::Graphics() : settings_(0, 0, 8),
                       window_(sf::VideoMode(CFG.getInt("window_width_px"), CFG.getInt("window_height_px")),
                                             "Gravity - simple simulation of gravitational forces", sf::Style::Default, settings_) {
    current_view_ = window_.getView();
    current_view_.setSize(CFG.getInt("window_width_px"), CFG.getInt("window_height_px"));
    current_view_.setCenter(CFG.getInt("window_width_px") / 2.0f, CFG.getInt("window_height_px") / 2.0f);
    window_.setView(current_view_);
    standard_view_ = current_view_;

    effect_generator_.initialize();
}

const bool Graphics::isWindowOpen() const {
    return window_.isOpen();
}

void Graphics::setStaticView() {
    current_view_ = window_.getView();
    window_.setView(standard_view_);
}

void Graphics::setDynamicView() {
    window_.setView(current_view_);
}

void Graphics::setStaticView(sf::View &view) {
    standard_view_ = view;
}

void Graphics::setDynamicView(sf::View &view) {
    current_view_ = view;
    window_.setView(current_view_);
}

sf::View& Graphics::getStaticView() {
    return standard_view_;
}

sf::View& Graphics::getDynamicView() {
    return current_view_;
}

sf::RenderWindow& Graphics::getWindow() {
    return window_;
}

void Graphics::clear() {
    effect_generator_.clear();
    window_.clear();
}

void Graphics::draw(const Background &object) {
    effect_generator_.addToTexture(object);
    effect_generator_.renderCurrentGaussianBlur(window_);
    effect_generator_.clear();
}

void Graphics::draw(const AbstractDrawableObject &object) {
    window_.draw(object);
}

void Graphics::display() {
    window_.display();
}