//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_GRAPHICS_H
#define GRAVITY_GRAPHICS_GRAPHICS_H

#include <SFML/Graphics.hpp>

#include <objects/Planet.h>
#include <objects/Background.h>
#include <graphics/EffectGenerator.h>
#include <UserInterface.h>
#include <Config.h>


class Graphics {

public:
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    static Graphics& getInstance() {
        static Graphics graphics_instance;
        return graphics_instance;
    }

    const bool isWindowOpen() const;

    void setStaticView();
    void setDynamicView();

    void clear();
    void draw(const Background &object);
    void draw(const AbstractDrawableObject &object);
    void display();

private:
    Graphics();

    void setStaticView(sf::View &view);
    void setDynamicView(sf::View &view);

    sf::RenderWindow& getWindow();

    sf::View& getStaticView();
    sf::View& getDynamicView();

    sf::ContextSettings settings_;
    sf::RenderWindow window_;
    sf::View standard_view_, current_view_;
    EffectGenerator effect_generator_;

    friend class UserInterface;

};


#endif //GRAVITY_GRAPHICS_GRAPHICS_H
