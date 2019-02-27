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

    // Physics
    static constexpr float DENSITY_KG_M_ = 5000000.0f;
    static constexpr float MAX_SET_VELOCITY_ = 200.0f;
};

#endif //GRAVITY_CONFIG_H
