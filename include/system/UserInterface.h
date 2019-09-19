//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_SYSTEM_USERINTERFACE_H
#define GRAVITY_SYSTEM_USERINTERFACE_H

#include <TGUI/TGUI.hpp>

#include <objects/AbstractDrawableObject.h>
#include <system/Config.h>


class UserInterface : public AbstractDrawableObject {

public:
    explicit UserInterface();

    UserInterface(const UserInterface&) = delete;
    UserInterface& operator=(const UserInterface&) = delete;

    void handleEvents();
    void drawGui();

private:
    enum class State {
        MENU,
        GALAXY
    };

    enum class MouseState {
        NOT_PRESSED,
        PRESSED
    };

    static tgui::Button::Ptr generateButton(const sf::Vector2i &pos,
                                            const sf::Vector2i &size,
                                            const std::string &text) {
        auto button = tgui::Button::create();
        button->setPosition(pos.x, pos.y);
        button->setText(text);
        button->setSize(size.x, size.y);
        return button;
    }

    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const;

    inline void addWidgets();

    inline void handleScrolling(sf::RenderWindow &graphics_window,
                                sf::View &view,
                                const sf::Vector2i &mouse_pos,
                                float zoom_delta);
    inline void handleKeyPressed(sf::RenderWindow &graphics_window,
                                 sf::View &view,
                                 const sf::Keyboard::Key &key_code);
    inline void handleInterfaceStates(sf::RenderWindow &graphics_window,
                                      const sf::Vector2i &mouse_pos,
                                      const sf::Vector2f &current_velocity);
    inline void setCursorRadius(float new_r);

    static constexpr int MENU_WIDTH_PX_ = 250;

    State state_;
    MouseState mouse_state_;

    sf::Vector2i previous_mouse_pos_;

    sf::CircleShape cursor_planet_;
    float cursor_r_;
    float current_zoom_;

    // velocity graphics representation
    sf::ConvexShape shaft_;
    sf::ConvexShape arrow_l_, arrow_r_;

    // menu
    tgui::Gui gui_;
    sf::RectangleShape menu_background_;

    tgui::Button::Ptr exit_button_, save_button_, load_button_, run_button_;
    tgui::ListBox::Ptr map_list_;
    tgui::EditBox::Ptr new_map_name_;
    tgui::Label::Ptr information_;
};


#endif //GRAVITY_SYSTEM_USERINTERFACE_H
