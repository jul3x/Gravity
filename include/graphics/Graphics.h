//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_GRAPHICS_H
#define GRAVITY_GRAPHICS_GRAPHICS_H

#include <list>

#include <SFML/Graphics.hpp>

#include <objects/Planet.h>
#include <objects/Background.h>
#include <graphics/UserInterface.h>
#include <graphics/EffectGenerator.h>
#include <Config.h>


class Graphics {

public:
    enum class EffectType {
        NONE,
        GAUSSIAN_BLUR
    };

    explicit Graphics();

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    const bool isWindowOpen() const;
    void handleEvents();

    void setStaticView();
    void setDynamicView();

    void clear();
    void draw(const AbstractDrawableObject &object, const Graphics::EffectType &effect);
    void display();

private:
    sf::ContextSettings settings_;
    sf::RenderWindow window_;
    sf::View standard_view_, current_view_;
    EffectGenerator effect_generator_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_GRAPHICS_H
