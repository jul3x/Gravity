//
// Created by jprolejko on 10.06.19.
//

#include <random>

#include <Star.h>

class Background : public sf::Drawable {
public:
    Background() : background_color_(20, 20, 20) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist_x(- Config::WINDOW_WIDTH_PIXELS_ / 2.0f, Config::WINDOW_WIDTH_PIXELS_ / 2.0f);
        std::uniform_real_distribution<float> dist_y(- Config::WINDOW_HEIGHT_PIXELS_ / 2.0f, Config::WINDOW_HEIGHT_PIXELS_ / 2.0f);
        std::uniform_real_distribution<float> dist_r(0.0f, 4.0f);
        std::uniform_real_distribution<float> dist_a(0.0f, 100.0f);

        for (int i = 0 ; i < 300; ++i)
        {
            stars_.emplace_back(sf::Vector2f{static_cast<float>(dist_x(mt)), static_cast<float>(dist_y(mt))}, 
                                static_cast<float>(dist_r(mt)), static_cast<float>(dist_a(mt)));
        }
    }

    void update(float time_elapsed) {
        for (auto & star : stars_)
        {
            star.updateAlpha(time_elapsed);
        }
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.clear(background_color_);
        for (const auto &star : stars_)
        {
            target.draw(star, states);
        }
    }

    const sf::Color background_color_;
    std::vector<Star> stars_;
};