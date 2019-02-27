//
// Created by jprolejko on 27.02.19.
//

#include "UserInterface.h"

UserInterface::UserInterface(sf::RenderWindow &window) : window_(window) {}

void UserInterface::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

        if (event.type == sf::Event::Resized)
        {
            auto visible_area = sf::Vector2f(event.size.width, event.size.height);
            auto current_view = window_.getView();

            current_view.setSize(visible_area);

            window_.setView(current_view);
        }
    }
}