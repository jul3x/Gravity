//
// Created by jprolejko on 27.02.19.
//

#include "Engine.h"


Engine::Engine() : graphics_(planets_) {
    planets_.emplace_back(sf::Vector2f(0.0, 0.0), sf::Vector2f(0.0, 0.0), 5.0f);
    planets_.emplace_back(sf::Vector2f(80.0, 200.0), sf::Vector2f(0.0, 0.0), 5.0f);
}

void Engine::update(int frame_rate) {
    restartClock();

    while (graphics_.isWindowOpen())
    {
        graphics_.handleEvents();

        graphics_.draw();
        ensureConstantFrameRate(frame_rate);
    }
}

void Engine::addPlanet(const sf::Vector2f &pos, const sf::Vector2f &vel, float r) {
    planets_.emplace_back(pos, vel, r);
}

void Engine::ensureConstantFrameRate(const int frame_rate) {
    time_ = clock_.restart();
    sf::Time time_for_sleep = sf::milliseconds(static_cast<int>(1000.0f / static_cast<float>(frame_rate))) - time_;
    sf::sleep(time_for_sleep);
    time_ = clock_.restart();
}

void Engine::restartClock() {
    time_ = clock_.restart();
}