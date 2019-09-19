//
// Created by jprolejko on 19.09.19.
//

#ifndef GRAVITY_SYSTEM_GRAVITYSYSTEMLOADER_H
#define GRAVITY_SYSTEM_GRAVITYSYSTEMLOADER_H

#include <list>
#include <string>

#include <objects/Planet.h>


class GravitySystemLoader {

public:
    GravitySystemLoader(const GravitySystemLoader&) = delete;
    GravitySystemLoader& operator=(const GravitySystemLoader&) = delete;

    GravitySystemLoader() = delete;

    static void saveGravitySystem(const std::list<Planet> &planets, const std::string &path, const std::string &name);
    static std::list<Planet> loadGravitySystem(const std::string &path, const std::string &name);
    static std::list<std::string> loadGravitySystems(const std::string &path);

};


#endif //GRAVITY_SYSTEM_GRAVITYSYSTEMLOADER_H
