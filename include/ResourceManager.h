//
// Created by jprolejko on 25.06.19.
//

#ifndef GRAVITY_RESOURCEMANAGER_H
#define GRAVITY_RESOURCEMANAGER_H

#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>

class ResourceManager {

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& getInstance() {
        static ResourceManager resource_manager_instance;
        return resource_manager_instance;
    }

    const sf::Texture& getTexture(const std::string &key) const {
        if (textures_.find(key) == textures_.end())
        {
            std::runtime_error(key + " is not a texture!");
        }

        return textures_.at(key);
    }

private:
    ResourceManager() {
        // change to more generic solution
        loadTexture("planet");
    }

    void loadTexture(const std::string &key) {
        sf::Texture texture;

        if (!texture.loadFromFile("data/" + key + ".png"))
        {
            std::runtime_error(key + " texture file not successfully loaded.");
        }

        textures_[key] = texture;
    }

    std::map<std::string, sf::Texture> textures_;
};


#endif //GRAVITY_RESOURCEMANAGER_H
