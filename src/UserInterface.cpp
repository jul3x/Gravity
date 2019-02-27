//
// Created by jprolejko on 27.02.19.
//


#include <iostream>

#include <Engine.h>
#include <UserInterface.h>
#include <Utils.h>


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
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            auto mouse_pos = sf::Mouse::getPosition(window_);
            auto new_mouse_pos = window_.mapPixelToCoords(mouse_pos);

            auto mouse_difference = utils::vectorLengthLimit(new_mouse_pos - previous_mouse_pos_,
                                                             Config::MAX_SET_VELOCITY_ * Config::PIXELS_PER_KM_);

            std::cout << mouse_difference.x << std::endl;
            Engine::getInstance().addPlanet(previous_mouse_pos_ / Config::PIXELS_PER_KM_,
                                            mouse_difference / Config::PIXELS_PER_KM_, 5.0f);
        }
    }
}