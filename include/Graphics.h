//
// Created by jprolejko on 26.02.19.
//

#ifndef GRAVITY_GRAPHICS_H
#define GRAVITY_GRAPHICS_H

#include <vector>

#include <SFML/Graphics.hpp>

#include <Planet.h>
#include <UserInterface.h>

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

    static constexpr float PIXELS_PER_KM_ = 1.0f;
    static constexpr float OBJECT_ZOOM_ = 10.0f;
    static constexpr int WINDOW_WIDTH_PIXELS_ = 1000;
    static constexpr int WINDOW_HEIGHT_PIXELS_ = 600;

    const sf::Color background_color_;

    const std::vector<Planet> &planets_;

    sf::ContextSettings settings_;
    sf::RenderWindow window_;

    UserInterface user_interface_;
};


#endif //GRAVITY_GRAPHICS_H
