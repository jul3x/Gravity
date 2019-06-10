//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_H
#define GRAVITY_GRAPHICS_H

#include <list>

#include <SFML/Graphics.hpp>

#include <Planet.h>
#include <UserInterface.h>
#include <Config.h>
#include <Background.h>

class Graphics {

public:
    explicit Graphics(const std::list<Planet> &planets);

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    const bool isWindowOpen() const;
    void handleEvents();

    void draw(float time_elapsed);

private:
    void draw(const Planet &planet);

    Background background_;
    const std::list<Planet> &planets_;

    sf::ContextSettings settings_;
    sf::RenderWindow window_;
    sf::View standard_view_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_H
