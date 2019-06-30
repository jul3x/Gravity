//
// Created by jprolejko on 27.02.19.
//

#ifndef GRAVITY_ENGINE_H
#define GRAVITY_ENGINE_H


#include <objects/Planet.h>
#include <graphics/Graphics.h>
#include <UserInterface.h>
#include <physics/Physics.h>


class Engine {

public:
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    static Engine& getInstance() {
        static Engine engine_instance;
        return engine_instance;
    }

    void update(int frame_rate);
    void addPlanet(const sf::Vector2f &pos,
                   const sf::Vector2f &vel,
                   float r);
    void destroyPlanet(const std::list<Planet>::iterator &current_planet);

private:
    Engine();

    void ensureConstantFrameRate(int frame_rate);
    void restartClock();

    Physics physics_;

    UserInterface user_interface_;

    sf::Clock clock_;
    sf::Time time_;

    std::list<Planet> planets_;
    Background background_;
};


#endif //GRAVITY_ENGINE_H
