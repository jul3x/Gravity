//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_H
#define GRAVITY_GRAPHICS_H

#include <vector>

#include <SFML/Graphics.hpp>

#include <Planet.h>
#include <UserInterface.h>
#include <Config.h>

class Graphics {

public:
    explicit Graphics(const std::vector<Planet> &planets);

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    const bool isWindowOpen() const;
    void handleEvents();

    void draw();

private:
    void draw(const Planet &planet);

    const sf::Color background_color_;

    const std::vector<Planet> &planets_;

    sf::ContextSettings settings_;
    sf::RenderWindow window_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_H
