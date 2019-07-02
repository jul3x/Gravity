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

    sf::Vector2i previous_mouse_pos_;

    sf::CircleShape cursor_planet_;
    float cursor_r_;
    float current_zoom_;

    // velocity graphics representation
    sf::ConvexShape shaft_;
    sf::ConvexShape arrow_l_, arrow_r_;
};


#endif //GRAVITY_GRAPHICS_USERINTERFACE_H
