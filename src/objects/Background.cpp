//
// Created by jprolejko on 12.06.19.
//

#include <Config.h>
#include <utils/Random.h>

#include <objects/Background.h>

Background::Background() {
    this->setColor(sf::Color(20, 20, 20));

    for (int i = 0 ; i < NUMBER_OF_STARS_; ++i)
    {
        sf::Vector2f position = {utils::getRandom<float>(0.0f, Config::WINDOW_WIDTH_PIXELS_),
                                 utils::getRandom<float>(0.0f, Config::WINDOW_HEIGHT_PIXELS_)};
        sf::Vector2f velocity = {utils::getRandom<float>(1.0f, 5.0f),
                                 utils::getRandom<float>(1.0f, 5.0f)};
        float radius = utils::getRandom<float>(1.0f, 5.0f);
        float alpha = utils::getRandom<float>(0.0f, 255.0f);
        stars_.push_back({position, velocity, radius, sf::Color(255, 255, 255, alpha)});
    }
}

float Background::getMass() const {
    return 0.0f;
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

