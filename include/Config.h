//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_CONFIG_H
#define GRAVITY_CONFIG_H

#include <memory>
#include <map>

class AbstractParamValue {

public:
    AbstractParamValue() = default;
    ~AbstractParamValue() = default;

};

template <typename T>
class ParamValue : public AbstractParamValue {

public:
    ParamValue(const T &value) : value_(value) {}
    T get() const {
        return value_;
    }

private:
    T value_;

};

class Config {

public:
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    static Config& getInstance() {
        static Config instance;
        return instance;
    }
    
    void initialize() {
        // TODO - loading from file
        params_["pixels_per_km"] = std::make_unique<ParamValue<float>>(1.0f);
        params_["window_width_px"] = std::make_unique<ParamValue<int>>(1500);
        params_["window_height_px"] = std::make_unique<ParamValue<int>>(900);

        params_["number_of_stars"] = std::make_unique<ParamValue<int>>(200);
        params_["min_star_velocity"] = std::make_unique<ParamValue<float>>(1.0f);
        params_["max_star_velocity"] = std::make_unique<ParamValue<float>>(5.0f);
        params_["min_star_r"] = std::make_unique<ParamValue<float>>(1.0f);
        params_["max_star_r"] = std::make_unique<ParamValue<float>>(5.0f);
        params_["background_color"] = std::make_unique<ParamValue<int>>(0x141414FF);

        params_["background_color"] = std::make_unique<ParamValue<int>>(0xFFFFFFA0);
        params_["background_color"] = std::make_unique<ParamValue<int>>(0x141414FF);

        

        // Graphics
        PIXELS_PER_KM_ = 1.0f;
        WINDOW_WIDTH_PIXELS_ = 1500;
        WINDOW_HEIGHT_PIXELS_ = 900;

        NUMBER_OF_STARS_ = 200;
        MIN_STAR_VELOCITY_ = 1.0f;
        MAX_STAR_VELOCITY_ = 5.0f;
        MIN_STAR_R_ = 1.0f;
        MAX_STAR_R_ = 5.0f;
        BACKGROUND_COLOR_ = 0x141414FF;

        // UI
        CURSOR_PLANET_COLOR_ = 0xFFFFFFA0;

        ARROW_COLOR_ = 0xFFFFFFC0;
        ARROW_WIDTH_ = 5.0f;

        MAX_PLANET_RADIUS_ = 100.0f;
        MIN_PLANET_RADIUS_ = 2.0f;
        
        MIN_WINDOW_ZOOMOUT_ = 0.5f;
        MAX_WINDOW_ZOOMOUT_ = 15.0f;

        VIEW_MOVING_SPEED_ = 30.0f;
        SCROLLING_SPEED_ = 0.1f;

        // Physics
        DENSITY_KG_M_ = 3000.0f;
        MAX_SET_VELOCITY_ = 500.0f;
        GRAVITY_CONST_ = 0.067f;
    }

    // Graphics
    float PIXELS_PER_KM_;
    int WINDOW_WIDTH_PIXELS_;
    int WINDOW_HEIGHT_PIXELS_;

    int NUMBER_OF_STARS_;
    float MIN_STAR_VELOCITY_;
    float MAX_STAR_VELOCITY_;
    float MIN_STAR_R_;
    float MAX_STAR_R_;
    int BACKGROUND_COLOR_;

    // UI
    int CURSOR_PLANET_COLOR_;

    int ARROW_COLOR_;
    float ARROW_WIDTH_;

    float MAX_PLANET_RADIUS_;
    float MIN_PLANET_RADIUS_;
    
    float MIN_WINDOW_ZOOMOUT_;
    float MAX_WINDOW_ZOOMOUT_;

    float VIEW_MOVING_SPEED_;
    float SCROLLING_SPEED_;

    // Physics
    float DENSITY_KG_M_;
    float MAX_SET_VELOCITY_;
    float GRAVITY_CONST_;

private:
    Config() = default;

    std::map<std::string, std::unique_ptr<AbstractParamValue>> params_;

};

#endif //GRAVITY_CONFIG_H
