//
// Created by jprolejko on 27.02.19.
//


#include <Engine.h>
#include <ResourceManager.h>
#include <utils/Geometry.h>
#include <graphics/Graphics.h>

#include <UserInterface.h>


UserInterface::UserInterface() {
    state_ = State::NOT_PRESSED;
    cursor_planet_.setTexture(&ResourceManager::getInstance().getTexture("planet"));
    cursor_planet_.setFillColor(sf::Color(Config::CURSOR_PLANET_COLOR_R_, Config::CURSOR_PLANET_COLOR_G_,
                                          Config::CURSOR_PLANET_COLOR_B_, Config::CURSOR_PLANET_COLOR_A_));
    setCursorRadius(5.0f);

    arrow_.setFillColor(sf::Color(Config::ARROW_COLOR_R_, Config::ARROW_COLOR_G_,
                                  Config::ARROW_COLOR_B_, Config::ARROW_COLOR_A_));

    arrow_.setOrigin(0.0f, Config::ARROW_WIDTH_ / 2.0f);
}

void UserInterface::handleEvents() {
    static sf::Event event;
    static auto &graphics_window = Graphics::getInstance().getWindow();
    auto mouse_pos = graphics_window.mapPixelToCoords(sf::Mouse::getPosition(graphics_window));
    auto mouse_difference = mouse_pos - previous_mouse_pos_;
    auto current_velocity = utils::vectorLengthLimit(mouse_difference,
                                                     Config::MAX_SET_VELOCITY_ * Config::PIXELS_PER_KM_);

    while (graphics_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            graphics_window.close();
        }

        if (event.type == sf::Event::Resized)
        {
            auto visible_area = sf::Vector2f(event.size.width, event.size.height);
            auto current_view = graphics_window.getView();

            current_view.setSize(visible_area);

            graphics_window.setView(current_view);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            previous_mouse_pos_ = mouse_pos;

            state_ = State::PRESSED;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            Engine::getInstance().addPlanet(previous_mouse_pos_ / Config::PIXELS_PER_KM_,
                                            current_velocity / Config::PIXELS_PER_KM_, cursor_r_);

            state_ = State::NOT_PRESSED;
        }

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                setCursorRadius(cursor_r_ + cursor_r_ * event.mouseWheelScroll.delta / 4.0f);
            }
            else
            {
                static auto current_zoom = 1.0f;
                auto view = graphics_window.getView();

                auto mouse_pos_from_center =
                    static_cast<sf::Vector2f>(sf::Mouse::getPosition(graphics_window)) -
                    static_cast<sf::Vector2f>(graphics_window.getSize()) / 2.0f;

                auto factor = event.mouseWheelScroll.delta < 0 ? -1.0f : 1.0f;

                view.setCenter(view.getCenter() + factor * mouse_pos_from_center * current_zoom / 10.0f);
                view.zoom(1.0f - event.mouseWheelScroll.delta * 0.1f);
                current_zoom = current_zoom * (1.0f - event.mouseWheelScroll.delta * 0.1f);

                graphics_window.setView(view);
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            auto view = graphics_window.getView();
            auto delta = sf::Vector2f(0.0f, 0.0f);
            auto scrolling_speed = 10.0f;

            if (event.key.code == sf::Keyboard::Left)
            {
                delta.x -= scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                delta.x += scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                delta.y -= scrolling_speed;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                delta.y += scrolling_speed;
            }

            view.move(delta);
            graphics_window.setView(view);
        }
    }

    switch (state_)
    {
        case State::NOT_PRESSED:
        {
            cursor_planet_.setPosition(mouse_pos);
            previous_mouse_pos_ = mouse_pos;
            break;
        }
        case State::PRESSED:
        {
            cursor_planet_.setPosition(previous_mouse_pos_);
            arrow_.setPosition(previous_mouse_pos_);
            arrow_.setSize({std::hypot(current_velocity.x, current_velocity.y), Config::ARROW_WIDTH_});
            arrow_.setRotation(static_cast<float>(
                std::atan2(current_velocity.y, current_velocity.x) / M_PI * 180.0f));

            break;
        }
        default:
        {
            throw std::runtime_error("[UserInterface] Wrong state!");
            break;
        }
    }
}

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (state_ == State::PRESSED)
    {
        target.draw(arrow_, states);
    }

    target.draw(cursor_planet_, states);
}

inline void UserInterface::setCursorRadius(float new_r) {
    if (new_r <= 0.0 || new_r >= Config::MAX_PLANET_RADIUS_)
    {
        return;
    }

    cursor_r_ = new_r;

    cursor_planet_.setOrigin(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_,
                             cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
    cursor_planet_.setRadius(cursor_r_ * Config::PIXELS_PER_KM_ * Config::OBJECT_ZOOM_);
}
