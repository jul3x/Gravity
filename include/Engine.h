//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_ENGINE_H
#define GRAVITY_ENGINE_H


#include <vector>

#include <Planet.h>
#include <Graphics.h>

class Engine {

public:
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    static Engine& getInstance() {
        static Engine engine_instance;
        return engine_instance;
    }

    void update(int frame_rate);
    void addPlanet(const sf::Vector2f &pos, const sf::Vector2f &vel, float r);

private:
    Engine();

    Graphics graphics_;

    std::vector<Planet> planets_;
};


#endif //GRAVITY_ENGINE_H
