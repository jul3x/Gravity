//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_ENGINE_H
#define GRAVITY_ENGINE_H


#include <vector>

#include <Planet.h>
#include <Graphics.h>
#include <Physics.h>

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

    void ensureConstantFrameRate(int frame_rate);
    void restartClock();

    Graphics graphics_;
    Physics physics_;

    sf::Clock clock_;
    sf::Time time_;

    std::list<Planet> planets_;
};


#endif //GRAVITY_ENGINE_H
