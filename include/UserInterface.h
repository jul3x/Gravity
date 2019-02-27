//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_USERINTERFACE_H
#define GRAVITY_USERINTERFACE_H


#include <SFML/Graphics.hpp>

class UserInterface {
    
public:
    explicit UserInterface(sf::RenderWindow &window);

    UserInterface(const UserInterface&) = delete;
    UserInterface& operator=(const UserInterface&) = delete;

    void handleEvents();

private:
    sf::RenderWindow &window_;

    sf::Vector2f previous_mouse_pos_;

};


#endif //GRAVITY_USERINTERFACE_H
