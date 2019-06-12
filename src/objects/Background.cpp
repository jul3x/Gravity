//
// Created by jprolejko on 12.06.19.
//


#include <random>

#include <Config.h>

#include <objects/Background.h>

Background::Background() : background_color_(20, 20, 20) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist_x(0.0f, Config::WINDOW_WIDTH_PIXELS_);
    std::uniform_real_distribution<float> dist_y(0.0f, Config::WINDOW_HEIGHT_PIXELS_);
    std::uniform_real_distribution<float> dist_r(1.0f, 5.0f);
    std::uniform_real_distribution<float> dist_vel(1.0f, 5.0f);
    std::uniform_real_distribution<float> dist_a(0.0f, 255.0f);

    for (int i = 0 ; i < 200; ++i)
    {
        stars_.emplace_back(sf::Vector2f{static_cast<float>(dist_x(mt)), static_cast<float>(dist_y(mt))},
                            sf::Vector2f{static_cast<float>(dist_vel(mt)), static_cast<float>(dist_vel(mt))},  
                            static_cast<float>(dist_r(mt)), static_cast<float>(dist_a(mt)));
    }
}

void Background::update(float time_elapsed) {
    for (auto & star : stars_)
    {
        star.update(time_elapsed);
    }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto &star : stars_)
    {
        target.draw(star, states);
    }
}

