//
// Created by jprolejko on 27.02.19.
//

#include <chrono>

#include <Engine.h>


Engine::Engine() : physics_(planets_) { 
    addPlanet({CFG.getInt("window_width_px") / 2.0f, CFG.getInt("window_height_px") / 2.0f}, {}, 50.0f); 
}

void Engine::update(int frame_rate) {
    restartClock();
    auto time_start = std::chrono::system_clock::now();

    while (Graphics::getInstance().isWindowOpen())
    {
        float time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now() - time_start).count() / 1000000.0f;
        time_start = std::chrono::system_clock::now();

        user_interface_.handleEvents();

        background_.update(time_elapsed);
        physics_.update(time_elapsed);

        for (auto it = explosions_.begin(); it != explosions_.end(); ++it)
        {
            if (it->update(time_elapsed))
            {
                auto next_it = std::next(it);
                explosions_.erase(it);
                it = next_it;
            }
        }

        // drawing
        {
            Graphics::getInstance().clear();
            Graphics::getInstance().setStaticView();
            Graphics::getInstance().draw(background_);
            Graphics::getInstance().setDynamicView();

            for (const auto &planet : planets_)
            {
                Graphics::getInstance().draw(planet);
            }

            Graphics::getInstance().draw(user_interface_);

            for (const auto &explo : explosions_)
            {
                Graphics::getInstance().draw(explo);
            }

            Graphics::getInstance().display();
        }

        ensureConstantFrameRate(frame_rate);
    }
}

void Engine::addPlanet(const sf::Vector2f &pos, const sf::Vector2f &vel, float r) {
    planets_.emplace_back(pos, vel, r);
}

void Engine::destroyPlanet(const std::list<Planet>::iterator &planet) {
    planets_.erase(planet);
    explosions_.emplace_back(planet->getPosition(), planet->getVelocity(), planet->getRadius());
}

void Engine::ensureConstantFrameRate(const int frame_rate) {
    time_ = clock_.restart();
    sf::Time time_for_sleep =
        sf::milliseconds(static_cast<int>(1000.0f / static_cast<float>(frame_rate))) - time_;
    sf::sleep(time_for_sleep);
    time_ = clock_.restart();
}

void Engine::restartClock() {
    time_ = clock_.restart();
}