//
// Created by jprolejko on 27.02.19.
//

#include <chrono>

#include <system/Engine.h>


Engine::Engine() : physics_(planets_),
                   state_(State::PAUSED) {
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

        if (state_ == State::OK)
        {
            background_.update(time_elapsed);
            physics_.update(time_elapsed);

            for (auto it = animations_.begin(); it != animations_.end(); ++it)
            {
                if ((*it)->update(time_elapsed))
                {
                    auto next_it = std::next(it);
                    animations_.erase(it);
                    it = next_it;
                }
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

            for (const auto &animation : animations_)
            {
                Graphics::getInstance().draw(*animation);
            }

            Graphics::getInstance().draw(user_interface_);

            Graphics::getInstance().setStaticView();
            user_interface_.drawGui();
            Graphics::getInstance().setDynamicView();

            Graphics::getInstance().display();
        }

        ensureConstantFrameRate(frame_rate);
    }
}

void Engine::setSimulationState(bool run) {
    state_ = run ? State::OK : State::PAUSED;
}

Engine::State Engine::getSimulationState() {
    return state_;
}

void Engine::updatePlanetsList(const std::list<Planet> &planets) {
    planets_ = planets;
}

void Engine::addPlanet(const sf::Vector2f &pos, const sf::Vector2f &vel, float r) {
    planets_.emplace_back(pos, vel, r);
    animations_.emplace_back(std::make_unique<SpawnAnimation>(pos, r));
}

void Engine::destroyPlanet(const std::list<Planet>::iterator &planet) {
    animations_.emplace_back(std::make_unique<Explosion>(planet->getPosition(), planet->getVelocity(), planet->getRadius()));
    planets_.erase(planet);
}

sf::Vector2i Engine::detectResolution() {
    int res_x = static_cast<int>(sf::VideoMode::getDesktopMode().width);
    int res_y = static_cast<int>(sf::VideoMode::getDesktopMode().height);

    std::cout << "[Engine] Screen resolution is: " << res_x << "px, " << res_y << "px." << std::endl;

    return {res_x, res_y};
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