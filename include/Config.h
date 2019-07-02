//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_CONFIG_H
#define GRAVITY_CONFIG_H

class Config {

public:
    // Graphics
    static constexpr float PIXELS_PER_KM_ = 1.0f;
    static constexpr float OBJECT_ZOOM_ = 1.0f;
    static constexpr int WINDOW_WIDTH_PIXELS_ = 1500;
    static constexpr int WINDOW_HEIGHT_PIXELS_ = 900;

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

    static constexpr float MAX_PLANET_RADIUS_ = 100.0f;

    // Physics
    static constexpr float DENSITY_KG_M_ = 5000.0f;
    static constexpr float MAX_SET_VELOCITY_ = 500.0f;
    static constexpr float GRAVITY_CONST = 0.067f; // TODO CHECK THOSE PARAMETERS
};

#endif //GRAVITY_CONFIG_H
