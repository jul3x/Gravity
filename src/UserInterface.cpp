//
// Created by jprolejko on 27.02.19.
//

#include <Engine.h>
#include <UserInterface.h>
#include <iostream>

UserInterface::UserInterface(sf::RenderWindow &window) : window_(window) {}

void UserInterface::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }

        if (event.type == sf::Event::Resized)
        {
            auto visible_area = sf::Vector2f(event.size.width, event.size.height);
            auto current_view = window_.getView();

            current_view.setSize(visible_area);

            window_.setView(current_view);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            auto mouse_pos = sf::Mouse::getPosition(window_);
            previous_mouse_pos_ = window_.mapPixelToCoords(mouse_pos);

            Engine::getInstance().addPlanet(previous_mouse_pos_ / Config::PIXELS_PER_KM_, sf::Vector2f(), 5.0f);
        }
    }
}