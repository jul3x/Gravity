//
// Created by jprolejko on 26.02.19.
//

#include <Graphics.h>

int main()
{
    constexpr int FRAME_RATE = 60;

    std::vector<Planet> planets;

    Graphics graphics(planets);

    planets.emplace_back(sf::Vector2f(0.0, 0.0), sf::Vector2f(0.0, 0.0), 5.0f);
    planets.emplace_back(sf::Vector2f(80.0, 200.0), sf::Vector2f(0.0, 0.0), 5.0f);
    graphics.restartClock();

    while (graphics.isWindowOpen())
    {
        graphics.handleEvents();



        graphics.draw();
        graphics.ensureConstantFrameRate(FRAME_RATE);
    }

    return 0;
}