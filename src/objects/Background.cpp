//
// Created by jprolejko on 12.06.19.
//

#include <utils/Numeric.h>
#include <Config.h>

#include <objects/Background.h>


Background::Background() {
    this->setColor(sf::Color(Config::getInstance().BACKGROUND_COLOR_));

    for (int i = 0 ; i < Config::getInstance().NUMBER_OF_STARS_; ++i)
    {
        sf::Vector2f position = {utils::getRandom<float>(0.0f, Config::getInstance().WINDOW_WIDTH_PIXELS_),
                                 utils::getRandom<float>(0.0f, Config::getInstance().WINDOW_HEIGHT_PIXELS_)};
        sf::Vector2f velocity = {utils::getRandom<float>(Config::getInstance().MIN_STAR_VELOCITY_, Config::getInstance().MAX_STAR_VELOCITY_),
                                 utils::getRandom<float>(Config::getInstance().MIN_STAR_VELOCITY_, Config::getInstance().MAX_STAR_VELOCITY_)};

        auto radius = utils::getRandom<float>(Config::getInstance().MIN_STAR_R_, Config::getInstance().MAX_STAR_R_);
        auto alpha = utils::getRandom<int>(0.0f, 255.0f);
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
    target.clear(this->getColor());
    
    for (const auto &star : stars_)
    {
        target.draw(star, states);
    }
}

