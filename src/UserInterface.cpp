//
// Created by jprolejko on 27.02.19.
//

#include <iostream> 

#include <Engine.h>
#include <ResourceManager.h>
#include <utils/Geometry.h>
#include <utils/Numeric.h>
#include <graphics/Graphics.h>

#include <UserInterface.h>


UserInterface::UserInterface() : gui_(Graphics::getInstance().getWindow()) {
    state_ = State::NOT_PRESSED;
    cursor_planet_.setTexture(&ResourceManager::getInstance().getTexture("planet"));
    cursor_planet_.setFillColor(sf::Color(CFG.getInt("cursor_planet_color")));
    setCursorRadius(10.0f);

    shaft_.setPointCount(3);
    arrow_l_.setPointCount(3);
    arrow_r_.setPointCount(3);

    sf::Color arrow_color(CFG.getInt("arrow_color"));
    shaft_.setFillColor(arrow_color);
    arrow_l_.setFillColor(arrow_color);
    arrow_r_.setFillColor(arrow_color);

    shaft_.setOrigin(0.0f, 0.0f);
    arrow_l_.setOrigin(0.0f, 0.0f);
    arrow_r_.setOrigin(0.0f, 0.0f);

    current_zoom_ = 1.0f;

    this->addWidgets();
}

void UserInterface::handleEvents() {
    static sf::Event event;
    static auto &graphics_window = Graphics::getInstance().getWindow();
    auto view = graphics_window.getView();
    auto mouse_pos = sf::Mouse::getPosition(graphics_window);
    auto mouse_difference = graphics_window.mapPixelToCoords(mouse_pos) -
        graphics_window.mapPixelToCoords(previous_mouse_pos_);
    auto current_velocity = utils::vectorLengthLimit(mouse_difference,
                                                     CFG.getFloat("max_set_velocity") * CFG.getFloat("pixels_per_km"));

    while (graphics_window.pollEvent(event))
    {
        gui_.handleEvent(event);

        switch (event.type)
        {
            case sf::Event::Closed:
            {
                graphics_window.close();
                break;
            }
            case sf::Event::Resized:
            {
                auto visible_area = sf::Vector2f(event.size.width, event.size.height);
                view.setSize(visible_area);

                auto dynamic_view = Graphics::getInstance().getDynamicView();
                dynamic_view.setSize(visible_area);
                dynamic_view.zoom(current_zoom_);
                Graphics::getInstance().setDynamicView(dynamic_view);

                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                previous_mouse_pos_ = mouse_pos;

                state_ = State::PRESSED;
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                Engine::getInstance().addPlanet(graphics_window.mapPixelToCoords(previous_mouse_pos_) /
                                                    CFG.getFloat("pixels_per_km"),
                                                current_velocity / CFG.getFloat("pixels_per_km"), cursor_r_);

                state_ = State::NOT_PRESSED;
                break;
            }
            case sf::Event::MouseWheelScrolled:
            {
                handleScrolling(graphics_window, view, mouse_pos, event.mouseWheelScroll.delta);
                break;
            }
            case sf::Event::KeyPressed:
            {
                handleKeyPressed(graphics_window, view, event.key.code);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    handleInterfaceStates(graphics_window, mouse_pos, current_velocity);
}

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (state_ == State::PRESSED && !utils::isNearlyEqual(shaft_.getLocalBounds().width, 0.0f, 0.01f))
    {
        target.draw(shaft_, states);
        target.draw(arrow_l_, states);
        target.draw(arrow_r_, states);
    }

    target.draw(cursor_planet_, states);
}

void UserInterface::drawGui() {
    gui_.draw();
}

inline void UserInterface::addWidgets() {
    auto exit_button = tgui::Button::create();
    exit_button->setPosition(75, 70);
    exit_button->setText("Exit");
    exit_button->setSize(100, 30);
    exit_button->connect("pressed", [&](){ Graphics::getInstance().getWindow().close(); });
    gui_.add(exit_button);
}

inline void UserInterface::handleScrolling(sf::RenderWindow &graphics_window, sf::View &view,
                                           const sf::Vector2i &mouse_pos, float zoom_delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        setCursorRadius(cursor_r_ + cursor_r_ * zoom_delta * CFG.getFloat("view_scrolling_speed"));
    }
    else
    {
        auto signum = zoom_delta < 0 ? -1.0f : 1.0f;

        auto zoom = 1.0f - zoom_delta * CFG.getFloat("view_scrolling_speed");
        if (utils::isBetween(current_zoom_ * zoom, CFG.getFloat("min_window_zoomout"), CFG.getFloat("max_window_zoomout")))
        {
            auto mouse_pos_from_center =
                static_cast<sf::Vector2f>(mouse_pos) -
                static_cast<sf::Vector2f>(graphics_window.getSize()) / 2.0f;
            view.setCenter(view.getCenter() + signum * mouse_pos_from_center * current_zoom_ * CFG.getFloat("view_scrolling_speed"));
            current_zoom_ = current_zoom_ * zoom;
            view.zoom(zoom);

            graphics_window.setView(view);
        }
    }
}

inline void UserInterface::handleKeyPressed(sf::RenderWindow &graphics_window, sf::View &view,
                                            const sf::Keyboard::Key &key_code) {
    auto delta = sf::Vector2f(0.0f, 0.0f);
    auto scrolling_speed = CFG.getFloat("view_moving_speed") * current_zoom_;

    switch (key_code)
    {
        case sf::Keyboard::Left:
        {
            delta.x -= scrolling_speed;
            break;
        }
        case sf::Keyboard::Right:
        {
            delta.x += scrolling_speed;
            break;
        }
        case sf::Keyboard::Up:
        {
            delta.y -= scrolling_speed;
            break;
        }
        case sf::Keyboard::Down:
        {
            delta.y += scrolling_speed;
            break;
        }
        default:
        {
            break;
        }
    }

    view.move(delta);
    graphics_window.setView(view);
}

inline void UserInterface::handleInterfaceStates(sf::RenderWindow &graphics_window, const sf::Vector2i &mouse_pos,
                                                 const sf::Vector2f &current_velocity) {
    switch (state_)
    {
        case State::NOT_PRESSED:
        {
            cursor_planet_.setPosition(graphics_window.mapPixelToCoords(mouse_pos));
            previous_mouse_pos_ = mouse_pos;
            break;
        }
        case State::PRESSED:
        {
            static float ARROW_LENGTH = CFG.getFloat("arrow_width") * 3.0f;
            auto mouse_coords = graphics_window.mapPixelToCoords(previous_mouse_pos_);
            cursor_planet_.setPosition(mouse_coords);

            shaft_.setPosition(mouse_coords);
            arrow_l_.setPosition(mouse_coords);
            arrow_r_.setPosition(mouse_coords);

            auto shaft_length = static_cast<float>(std::hypot(current_velocity.x, current_velocity.y)) - ARROW_LENGTH;
            auto arrow_rotation = static_cast<float>(std::atan2(current_velocity.y, current_velocity.x) / M_PI * 180.0f);

            // do not show arrow when velocity is really small
            shaft_length = utils::isNearlyEqual(shaft_length, - ARROW_LENGTH, ARROW_LENGTH * 2.0f) ? 0.0f : shaft_length;

            shaft_.setPoint(0, {0, 0});
            shaft_.setPoint(1, {shaft_length, - CFG.getFloat("arrow_width") / 2.0f});
            shaft_.setPoint(2, {shaft_length, CFG.getFloat("arrow_width") / 2.0f});
            
            arrow_l_.setPoint(0, {shaft_length, 0});
            arrow_l_.setPoint(1, {shaft_length + ARROW_LENGTH, 0});
            arrow_l_.setPoint(2, {shaft_length - ARROW_LENGTH, - ARROW_LENGTH});

            arrow_r_.setPoint(0, {shaft_length, 0});
            arrow_r_.setPoint(1, {shaft_length + ARROW_LENGTH, 0});
            arrow_r_.setPoint(2, {shaft_length - ARROW_LENGTH, ARROW_LENGTH});

            shaft_.setRotation(arrow_rotation);
            arrow_l_.setRotation(arrow_rotation);
            arrow_r_.setRotation(arrow_rotation);

            break;
        }
        default:
        {
            throw std::runtime_error("[UserInterface] Wrong state!");
            break;
        }
    }
}

inline void UserInterface::setCursorRadius(float new_r) {
    if (!utils::isBetween(new_r, CFG.getFloat("min_planet_r"), CFG.getFloat("max_planet_r")))
    {
        return;
    }

    cursor_r_ = new_r;

    cursor_planet_.setOrigin(cursor_r_ * CFG.getFloat("pixels_per_km"), cursor_r_ * CFG.getFloat("pixels_per_km"));
    cursor_planet_.setRadius(cursor_r_ * CFG.getFloat("pixels_per_km"));
}
