//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_CONFIG_H
#define GRAVITY_CONFIG_H

#include <map>
#include <iostream>


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

        // Graphics
        float_params_["pixels_per_km"] = 1.0f;
        int_params_["window_width_px"] = 1500;
        int_params_["window_height_px"] = 900;

        int_params_["number_of_stars"] = 100;
        float_params_["min_star_velocity"] = 1.0f;
        float_params_["max_star_velocity"] = 5.0f;
        float_params_["min_star_r"] = 1.0f;
        float_params_["max_star_r"] = 5.0f;
        int_params_["background_color"] = 0x141414FF;

        // UI
        int_params_["cursor_planet_color"] = 0xFFFFFFA0;
        
        int_params_["arrow_color"] = 0xFFFFFFFF;
        float_params_["arrow_width"] = 5.0f;
        
        float_params_["min_planet_r"] = 2.0f;
        float_params_["max_planet_r"] = 100.0f;

        float_params_["min_window_zoomout"] = 0.5f;
        float_params_["max_window_zoomout"] = 15.0f;

        float_params_["view_moving_speed"] = 30.0f;
        float_params_["view_scrolling_speed"] = 0.1f;

        // Physics
        float_params_["density_kg_m"] = 3000.0f;
        float_params_["max_set_velocity"] = 500.0f;
        float_params_["gravity_const"] = 0.067f;
    }

    int getInt(const std::string &key) const {
        if (int_params_.find(key) == int_params_.end())
        {
            std::cerr << "[Config] Param " << key << " not found!" << std::endl;
            return 0;
        }

        return int_params_.at(key);
    }

    float getFloat(const std::string &key) const {
        if (float_params_.find(key) == float_params_.end())
        {
            std::cerr << "[Config] Param " << key << " not found!" << std::endl;
            return 0;
        }

        return float_params_.at(key);
    }

private:
    Config() = default;

    std::map<std::string, int> int_params_;
    std::map<std::string, float> float_params_;

};

#define CFG Config::getInstance()

#endif //GRAVITY_CONFIG_H
