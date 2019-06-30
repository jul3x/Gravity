//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_GRAPHICS_USERINTERFACE_H
#define GRAVITY_GRAPHICS_USERINTERFACE_H


#include <objects/AbstractDrawableObject.h>
#include <Config.h>

class UserInterface : public AbstractDrawableObject {
    
public:
    explicit UserInterface();

    UserInterface(const UserInterface&) = delete;
    UserInterface& operator=(const UserInterface&) = delete;

    void handleEvents();

private:
    enum class State {
        NOT_PRESSED,
        PRESSED
    };

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    inline void setCursorRadius(float new_r);

    State state_;

    sf::Vector2f previous_mouse_pos_;

    sf::CircleShape cursor_planet_;
    float cursor_r_;

    sf::RectangleShape arrow_;
};


#endif //GRAVITY_GRAPHICS_USERINTERFACE_H
