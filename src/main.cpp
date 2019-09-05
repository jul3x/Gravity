//
// Created by jprolejko on 26.02.19.
//

#include <Config.h>
#include <Engine.h>

int main()
{
    constexpr int FRAME_RATE = 60;

    CFG.initialize("data/config.j3x");

    ResourceManager::getInstance().lazyLoadTexture("planet");
    ResourceManager::getInstance().lazyLoadTexture("explosion1");
    ResourceManager::getInstance().lazyLoadTexture("explosion2");
    ResourceManager::getInstance().lazyLoadTexture("explosion3");
    Engine::getInstance().update(FRAME_RATE);

    return 0;
}