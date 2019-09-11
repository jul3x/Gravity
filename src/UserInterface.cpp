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
    mouse_state_ = MouseState::NOT_PRESSED;
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

    menu_background_.setSize({UserInterface::MENU_WIDTH_PX_,
                              static_cast<float>(Graphics::getInstance().getWindow().getSize().y) + 100 /* titlebar */});
    menu_background_.setPosition(0.0f, 0.0f);
    menu_background_.setFillColor({255, 255, 255, 20});

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

    if (utils::isPointInRectangle(static_cast<sf::Vector2f>(mouse_pos), {0.0f, 0.0f},
                                  {UserInterface::MENU_WIDTH_PX_, static_cast<float>(graphics_window.getSize().y)}))
    {
        state_ = State::MENU;
    }
    else
    {
        state_ = State::GALAXY;
    }

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
                if (state_ != State::MENU)
                {
                    previous_mouse_pos_ = mouse_pos;
                    mouse_state_ = MouseState::PRESSED;
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (mouse_state_ == MouseState::PRESSED)
                {
                    Engine::getInstance().addPlanet(graphics_window.mapPixelToCoords(previous_mouse_pos_) /
                                                        CFG.getFloat("pixels_per_km"),
                                                    current_velocity / CFG.getFloat("pixels_per_km"), cursor_r_);
                }

                mouse_state_ = MouseState::NOT_PRESSED;
                break;
            }
            case sf::Event::MouseWheelScrolled:
            {
                if (state_ != State::MENU)
                {
                    handleScrolling(graphics_window, view, mouse_pos, event.mouseWheelScroll.delta);
                }
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
    if (mouse_state_ == MouseState::PRESSED && !utils::isNearlyEqual(shaft_.getLocalBounds().width, 0.0f, 0.01f))
    {
        target.draw(shaft_, states);
        target.draw(arrow_l_, states);
        target.draw(arrow_r_, states);
    }

    if (state_ != State::MENU || mouse_state_ == MouseState::PRESSED)
    {
        target.draw(cursor_planet_, states);
    }
}

void UserInterface::drawGui() {
    Graphics::getInstance().getWindow().draw(menu_background_);
    gui_.draw();
}

inline void UserInterface::addWidgets() {
    static const sf::Vector2i SIZE = {140, 30};
    static int POS_X = (UserInterface::MENU_WIDTH_PX_ - SIZE.x) / 2;

    auto exit_button = UserInterface::generateButton({POS_X, 70}, SIZE, "Exit");
    exit_button->connect("pressed", [&](){ Graphics::getInstance().getWindow().close(); });
    gui_.add(exit_button);

    auto new_map_name = tgui::EditBox::create();
    new_map_name->setSize(SIZE.x, SIZE.y);
    new_map_name->setPosition(POS_X, 150);
    new_map_name->setText("New map name");
    gui_.add(new_map_name);

    auto save_button = UserInterface::generateButton({POS_X, 180}, SIZE, "Save system");
    save_button->connect("pressed", [&](){ Graphics::getInstance().getWindow().close(); });
    gui_.add(save_button);

    auto map_list = tgui::ListBox::create();
    map_list->setSize(SIZE.x, SIZE.y * 4);
    map_list->setItemHeight(SIZE.y);
    map_list->setPosition(POS_X, 270);
    map_list->addItem("map1");
    map_list->addItem("map2");
    map_list->addItem("map3");
    map_list->addItem("map4");
    map_list->addItem("map5");
    map_list->addItem("map6");
    gui_.add(map_list);

    auto load_button = UserInterface::generateButton({POS_X, 390}, SIZE, "Load system");
    //load_button->connect("pressed", [&](){ Graphics::getInstance().getWindow().close(); });
    gui_.add(load_button);
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
    switch (mouse_state_)
    {
        case MouseState::NOT_PRESSED:
        {
            cursor_planet_.setPosition(graphics_window.mapPixelToCoords(mouse_pos));
            previous_mouse_pos_ = mouse_pos;
            break;
        }
        case MouseState::PRESSED:
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
