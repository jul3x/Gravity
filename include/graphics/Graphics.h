//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_GRAPHICS_H
#define GRAVITY_GRAPHICS_GRAPHICS_H

#include <SFML/Graphics.hpp>

#include <objects/Planet.h>
#include <objects/Background.h>
#include <graphics/UserInterface.h>
#include <graphics/EffectGenerator.h>
#include <Config.h>


class Graphics {

public:
    explicit Graphics();

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    const bool isWindowOpen() const;
    void handleEvents();

    void setStaticView();
    void setDynamicView();

    void clear();
    void draw(const Background &object);
    void draw(const AbstractDrawableObject &object);
    void display();

private:
    sf::ContextSettings settings_;
    sf::RenderWindow window_;
    sf::View standard_view_, current_view_;
    EffectGenerator effect_generator_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_GRAPHICS_H
