//
// Created by jprolejko on 19.09.19.
//


#include <list>
#include <string>
#include <fstream>
#include <experimental/filesystem>

#include <system/GravitySystemLoader.h>

void GravitySystemLoader::saveGravitySystem(const std::list<Planet> &planets, const std::string &path, const std::string &name) {
    if (std::experimental::filesystem::exists(path + name))
    {
        throw std::runtime_error("File already exists!");
    }

    std::ofstream system_file(path + name);

    if (system_file)
    {
        for (const auto &p : planets)
        {
            system_file << p.getPosition().x << " " << p.getPosition().y << " "
                        << p.getVelocity().x << " " << p.getVelocity().y << " "
                        << p.getRadius() << std::endl;
        }
    }
    else
    {
        throw std::runtime_error("Failed to open file!");
    }
}

std::list<Planet> GravitySystemLoader::loadGravitySystem(const std::string &path, const std::string &name) {
    std::ifstream system_file(path + name);
    std::list<Planet> planets;

    if (system_file)
    {
        float x, y, vx, vy, r;

        while (system_file >> x >> y >> vx >> vy >> r)
        {
            planets.push_back({{x, y}, {vx, vy}, r});
        }
    }
    else
    {
        throw std::logic_error("System file not found! This should not happen during standard runtime.");
    }

    return planets;
}

 std::list<std::string> GravitySystemLoader::loadGravitySystems(const std::string &path) {
    std::list<std::string> systems;

    for (const auto &system : std::experimental::filesystem::directory_iterator(path))
    {
        std::string name = system.path().string();
        name.erase(0, name.rfind('/') + 1);
        systems.push_back(name);
    }

    return systems;
}
