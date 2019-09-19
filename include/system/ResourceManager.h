//
// Created by jprolejko on 25.06.19.
//

#ifndef GRAVITY_SYSTEM_RESOURCEMANAGER_H
#define GRAVITY_SYSTEM_RESOURCEMANAGER_H

#include <list>
#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <TGUI/TGUI.hpp>

#include <system/GravitySystemLoader.h>
#include <objects/Planet.h>


class ResourceManager {

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& getInstance();

    sf::Texture& getTexture(const std::string &key);
    sf::Shader& getShader(const std::string &key);

    tgui::Theme& getTheme(const std::string &key);

    bool saveGravitySystem(const std::list<Planet> &planets, const std::string &path, const std::string &name) const;
    std::list<Planet> getGravitySystem(const std::string &path, const std::string &name) const;
    std::list<std::string> getGravitySystems(const std::string &path) const;

    void lazyLoadTexture(const std::string &key);

private:
    ResourceManager() = default;

    void loadTexture(const std::string &key);
    void loadShader(const std::string &key);

    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Shader> shaders_;
    std::map<std::string, tgui::Theme> themes_;
};


#endif //GRAVITY_SYSTEM_RESOURCEMANAGER_H
