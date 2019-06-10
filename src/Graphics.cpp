//
// Created by jprolejko on 26.02.19.
//

#include <Graphics.h>


Graphics::Graphics(const std::list<Planet> &planets) :
                            planets_(planets),
                            settings_(0, 0, 8),
                            window_(sf::VideoMode(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_),
                                    "Gravity", sf::Style::Default, settings_),
                            user_interface_(window_) {
    auto current_view = window_.getView();
    current_view.setSize(Config::WINDOW_WIDTH_PIXELS_, Config::WINDOW_HEIGHT_PIXELS_);
    current_view.setCenter(0.0f, 0.0f);
    window_.setView(current_view);
    standard_view_ = current_view;
}

const bool Graphics::isWindowOpen() const {
    return window_.isOpen();
}

void Graphics::handleEvents() {
    user_interface_.handleEvents();
}

void Graphics::draw(float time_elapsed) {
    background_.update(time_elapsed);
    auto current_view = window_.getView();
    window_.setView(standard_view_);
    window_.draw(background_);
    window_.setView(current_view);

    for (const auto &planet : planets_)
    {
        draw(planet);
    }

    user_interface_.draw();

    window_.display();
}

void Graphics::draw(const Planet &planet) {
    static sf::CircleShape planet_shape;
    planet_shape.setPosition(planet.getPosition() * Config::PIXELS_PER_KM_);

    auto pixel_radius = planet.getRadius() * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_;
    planet_shape.setRadius(pixel_radius);
    planet_shape.setOrigin(pixel_radius, pixel_radius);

    planet_shape.setFillColor(planet.getColor());

    window_.draw(planet_shape);
}