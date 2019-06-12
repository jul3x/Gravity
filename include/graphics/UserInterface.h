//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_GRAPHICS_USERINTERFACE_H
#define GRAVITY_GRAPHICS_USERINTERFACE_H


#include <SFML/Graphics.hpp>

#include <Config.h>

class UserInterface {
    
public:
    explicit UserInterface(sf::RenderWindow &window);

    UserInterface(const UserInterface&) = delete;
    UserInterface& operator=(const UserInterface&) = delete;

    void handleEvents();
    void draw();

private:
    enum class State {
        NOT_PRESSED,
        PRESSED
    };

    void drawCursorPlanet();
    void drawArrow();
    void setCursorRadius(float new_r);

    sf::RenderWindow &window_;

    State state_;

    sf::Vector2f previous_mouse_pos_;

    sf::CircleShape cursor_planet_;
    float cursor_r_;

    sf::RectangleShape arrow_;
};


#endif //GRAVITY_GRAPHICS_USERINTERFACE_H
