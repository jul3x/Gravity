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
#include <Config.h>


class Graphics {

public:
    explicit Graphics();

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    const bool isWindowOpen() const;
    void handleEvents();

    void draw(const AbstractDrawableObject &object);
    void drawBackground();
    void display();

private:
    Background background_;

    sf::ContextSettings settings_;
    sf::RenderWindow window_;
    sf::RenderTexture background_texture_, background_texture_2_;
    sf::View standard_view_;
    sf::Shader shader_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_GRAPHICS_H
