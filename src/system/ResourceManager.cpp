//
// Created by jprolejko on 26.06.2019.
//

#include <iostream>

#include <system/ResourceManager.h>


ResourceManager& ResourceManager::getInstance() {
    static ResourceManager resource_manager_instance;
    return resource_manager_instance;
}

sf::Texture& ResourceManager::getTexture(const std::string &key) {
    if (textures_.find(key) == textures_.end())
    {
        try
        {
            loadTexture(key);
            std::cout << "[ResourceManager] Texture " << key << " is loaded!" << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    return textures_.at(key);
}

sf::Shader& ResourceManager::getShader(const std::string &key) {
    if (shaders_.find(key) == shaders_.end())
    {
        try
        {
            loadShader(key);
            std::cout << "[ResourceManager] Shader " << key << " is loaded!" << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    return shaders_.at(key);
}

std::list<Planet> ResourceManager::getGravitySystem(const std::string &name) {
    // TODO - make planet loading

    try
    {
        // return gravity_system_loader_.loadGravitySystem(name);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return std::list<Planet>();
}

std::list<std::string> ResourceManager::getGravitySystems(const std::string &path) {
    // TODO make planet loading
    try
    {
        // return gravity_system_loader_.loadGravitySystems(path);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return {};
}

void ResourceManager::lazyLoadTexture(const std::string &key) {
    loadTexture(key);
}

void ResourceManager::loadTexture(const std::string &key) {
    if (!textures_[key].loadFromFile("data/textures/" + key + ".png"))
    {
        throw std::runtime_error("[ResourceManager] " + key + " texture file not successfully loaded.");
    }
}

void ResourceManager::loadShader(const std::string &key) {
    if (!sf::Shader::isAvailable())
    {
        throw std::runtime_error("[ResourceManager] Shaders are not available!");
    }

    if (!shaders_[key].loadFromFile("data/shaders/" + key + ".frag", sf::Shader::Fragment))
    {
        throw std::runtime_error("[ResourceManager] " + key + " shader file not found or is corrupted!");
    }
}