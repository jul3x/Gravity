//
// Created by jprolejko on 27.02.19.
//


#include <iostream>
#include <cmath>

#include <Engine.h>
#include <graphics/UserInterface.h>
#include <utils/Utils.h>


UserInterface::UserInterface(sf::RenderWindow &window) : window_(window) {
    state_ = State::NOT_PRESSED;

    cursor_planet_.setFillColor(sf::Color(Config::CURSOR_PLANET_COLOR_R_, Config::CURSOR_PLANET_COLOR_G_,
                                          Config::CURSOR_PLANET_COLOR_B_, Config::CURSOR_PLANET_COLOR_A_));
    setCursorRadius(5.0f);

    arrow_.setFillColor(sf::Color(Config::ARROW_COLOR_R_, Config::ARROW_COLOR_G_,
                                  Config::ARROW_COLOR_B_, Config::ARROW_COLOR_A_));

    arrow_.setOrigin(0.0f, Config::ARROW_WIDTH_ / 2.0f);
}

void UserInterface::handleEvents() {
    static sf::Event event;
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
            auto mouse_difference = new_mouse_pos - previous_mouse_pos_;
            auto velocity = utils::vectorLengthLimit(mouse_difference,
                                                     Config::MAX_SET_VELOCITY_ * Config::PIXELS_PER_KM_);

            Engine::getInstance().addPlanet(previous_mouse_pos_ / Config::PIXELS_PER_KM_,
                                            velocity / Config::PIXELS_PER_KM_, cursor_r_);

            state_ = State::NOT_PRESSED;
        }

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                setCursorRadius(cursor_r_ + event.mouseWheelScroll.delta / 4.0f);
            }
            else
            {
                auto view = window_.getView();

                auto mouse_pos_from_center = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window_)) -
                                             static_cast<sf::Vector2f>(window_.getSize()) / 2.0f;

                auto factor = event.mouseWheelScroll.delta < 0 ? -1.0f : 1.0f;

                view.setCenter(view.getCenter() + factor * mouse_pos_from_center / 5.0f);
                view.zoom(1.0f - event.mouseWheelScroll.delta * 0.1f);


                window_.setView(view);
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            auto view = window_.getView();
            auto delta_x = 0.0f;
            auto delta_y = 0.0f;
            auto scrolling_speed = 10.0f;

            if (event.key.code == sf::Keyboard::Left)
            {
                delta_x -= scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                delta_x += scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                delta_y -= scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                delta_y += scrolling_speed;
            }

            view.move(delta_x, delta_y);
            window_.setView(view);
        }
    }
}

void UserInterface::draw() {
    drawCursorPlanet();
    drawArrow();
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

void UserInterface::drawArrow() {
    if (state_ == State::PRESSED)
    {
        auto mouse_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

        auto mouse_difference = mouse_pos - previous_mouse_pos_;
        auto velocity = utils::vectorLengthLimit(mouse_difference,
                                                 Config::MAX_SET_VELOCITY_ * Config::PIXELS_PER_KM_);

        arrow_.setPosition(previous_mouse_pos_);
        arrow_.setSize({std::hypot(velocity.x, velocity.y), Config::ARROW_WIDTH_});
        arrow_.setRotation(static_cast<float>(std::atan2(velocity.y, velocity.x) / M_PI * 180.0f));

        window_.draw(arrow_);
    }
}

void UserInterface::setCursorRadius(float new_r) {
    if (new_r <= 0.0 || new_r >= Config::MAX_PLANET_RADIUS_)
    {
        return;
    }

    cursor_r_ = new_r;

    cursor_planet_.setOrigin(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_,
                             cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
    cursor_planet_.setRadius(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
}
