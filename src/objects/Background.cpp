//
// Created by jprolejko on 12.06.19.
//

#include <utils/Numeric.h>
#include <Config.h>

#include <objects/Background.h>


Background::Background() {
    this->setColor(sf::Color(CFG.getInt("background_color")));

    for (int i = 0 ; i < CFG.getInt("number_of_stars"); ++i)
    {
        sf::Vector2f position = {utils::getRandom<float>(0.0f, CFG.getInt("window_width_px")),
                                 utils::getRandom<float>(0.0f, CFG.getInt("window_height_px"))};
        sf::Vector2f velocity = {utils::getRandom<float>(CFG.getFloat("min_star_velocity"), CFG.getFloat("max_star_velocity")),
                                 utils::getRandom<float>(CFG.getFloat("min_star_velocity"), CFG.getFloat("max_star_velocity"))};

        auto radius = utils::getRandom<float>(CFG.getFloat("min_star_r"), CFG.getFloat("max_star_r"));
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

