//
// Created by jprolejko on 26.02.19.
//

#include <Graphics.h>


Graphics::Graphics(const std::vector<Planet> &planets) :
                            planets_(planets),
                            settings_(0, 0, 8),
                            view_action_(sf::FloatRect(0.0f, 0.0f, WINDOW_WIDTH_PIXELS_, WINDOW_HEIGHT_PIXELS_)),
                            window_(sf::VideoMode(WINDOW_WIDTH_PIXELS_, WINDOW_HEIGHT_PIXELS_),
                                    "Gravity", sf::Style::Default, settings_),
                            background_color_(10,10,30) {
    window_.setView(view_action_);
}

const bool Graphics::isWindowOpen() const {
    return window_.isOpen();
}

void Graphics::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

        if (event.type == sf::Event::Resized)
        {
            auto visible_area = sf::Vector2f(event.size.width, event.size.height);

            view_action_.setSize(visible_area);
        }
    }
}

void Graphics::draw() {
    window_.clear(background_color_);

    for (const auto &planet : planets_)
    {
        draw(planet);
    }

    window_.display();
}

void Graphics::draw(const Planet &planet) {
    sf::CircleShape planet_shape;
    planet_shape.setPosition(planet.getPosition() * PIXELS_PER_KM_);
    planet_shape.setRadius(planet.getRadius() * PIXELS_PER_KM_ * OBJECT_ZOOM_);
    planet_shape.setFillColor(planet.getColor());

    window_.draw(planet_shape);
}