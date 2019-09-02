//
// Created by jprolejko on 25.06.19.
//

#ifndef GRAVITY_RESOURCEMANAGER_H
#define GRAVITY_RESOURCEMANAGER_H

#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

class ResourceManager {

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& getInstance();

    sf::Texture& getTexture(const std::string &key);
    sf::Shader& getShader(const std::string &key);
    void lazyLoadTexture(const std::string &key);

private:
    ResourceManager() = default;

    void loadTexture(const std::string &key);
    void loadShader(const std::string &key);

    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Shader> shaders_;
};


#endif //GRAVITY_RESOURCEMANAGER_H
