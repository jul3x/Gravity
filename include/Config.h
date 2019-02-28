//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_CONFIG_H
#define GRAVITY_CONFIG_H

class Config {

public:
    // Graphics
    static constexpr float PIXELS_PER_KM_ = 1.0f;
    static constexpr float OBJECT_ZOOM_ = 10.0f;
    static constexpr int WINDOW_WIDTH_PIXELS_ = 1000;
    static constexpr int WINDOW_HEIGHT_PIXELS_ = 600;

    // UI
    static constexpr int CURSOR_PLANET_COLOR_R_ = 255;
    static constexpr int CURSOR_PLANET_COLOR_G_ = 255;
    static constexpr int CURSOR_PLANET_COLOR_B_ = 255;
    static constexpr int CURSOR_PLANET_COLOR_A_ = 100;

    static constexpr int ARROW_COLOR_R_ = 255;
    static constexpr int ARROW_COLOR_G_ = 255;
    static constexpr int ARROW_COLOR_B_ = 255;
    static constexpr int ARROW_COLOR_A_ = 255;
    static constexpr float ARROW_WIDTH_ = 5.0f;

    // Physics
    static constexpr float DENSITY_KG_M_ = 5000000.0f;
    static constexpr float MAX_SET_VELOCITY_ = 200.0f;
};

#endif //GRAVITY_CONFIG_H
