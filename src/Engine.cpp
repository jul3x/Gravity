//
// Created by jprolejko on 27.02.19.
//

#include <Engine.h>


Engine::Engine() : graphics_(), physics_(planets_) { 
    addPlanet({Config::WINDOW_WIDTH_PIXELS_ / 2.0f, Config::WINDOW_HEIGHT_PIXELS_ / 2.0f}, {}, 15.0f); 
}

void Engine::update(int frame_rate) {
    restartClock();

    while (graphics_.isWindowOpen())
    {
        float time_elapsed = 1.0f / static_cast<float>(frame_rate);

        graphics_.handleEvents();

        background_.update(time_elapsed);
        physics_.update(time_elapsed);
        
        // drawing
        {
            graphics_.clear();
            graphics_.setStaticView();
            graphics_.draw(background_);
            graphics_.setDynamicView();
            for (const auto &planet : planets_)
            {
                graphics_.draw(planet);
            }
            graphics_.display();
        }

        ensureConstantFrameRate(frame_rate);
    }
}

void Engine::addPlanet(const sf::Vector2f &pos, const sf::Vector2f &vel, float r) {
    planets_.emplace_back(pos, vel, r);
}

void Engine::destroyPlanet(const std::list<Planet>::iterator &planet) {
    planets_.erase(planet);
    // explosion will be created and triggered here
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