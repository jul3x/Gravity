//
// Created by jprolejko on 27.02.19.
//


#include <iostream>

#include <Engine.h>
#include <UserInterface.h>
#include <Utils.h>


UserInterface::UserInterface(sf::RenderWindow &window) : window_(window) {
    state_ = State::NOT_PRESSED;

    cursor_planet_.setFillColor(sf::Color(255, 255, 255, 100));

    setCursorRadius(5.0f);
}

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

            state_ = State::PRESSED;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            auto mouse_pos = sf::Mouse::getPosition(window_);
            auto new_mouse_pos = window_.mapPixelToCoords(mouse_pos);

            auto mouse_difference = utils::vectorLengthLimit(new_mouse_pos - previous_mouse_pos_,
                                                             Config::MAX_SET_VELOCITY_ * Config::PIXELS_PER_KM_);

            Engine::getInstance().addPlanet(previous_mouse_pos_ / Config::PIXELS_PER_KM_,
                                            mouse_difference / Config::PIXELS_PER_KM_, cursor_r_);

            state_ = State::NOT_PRESSED;
        }

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            setCursorRadius(cursor_r_ + event.mouseWheelScroll.delta / 4.0f);
        }
    }
}

void UserInterface::draw() {
    drawCursorPlanet();
}

void UserInterface::drawCursorPlanet() {
    if (state_ == State::NOT_PRESSED)
    {
        auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
        cursor_planet_.setPosition(mouse_pos);
    }
    else if (state_ == State::PRESSED)
    {
        cursor_planet_.setPosition(previous_mouse_pos_);
    }

    window_.draw(cursor_planet_);
}

void UserInterface::setCursorRadius(float new_r) {
    if (new_r <= 0.0)
    {
        return;
    }

    cursor_r_ = new_r;

    cursor_planet_.setOrigin(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_,
                             cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
    cursor_planet_.setRadius(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
}
