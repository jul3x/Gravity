//
// Created by jprolejko on 26.02.19.
//

#include <Config.h>
#include <Engine.h>

int main()
{
    constexpr int FRAME_RATE = 60;

    Config::getInstance().getInstance().initialize();

    Engine::getInstance().update(FRAME_RATE);

    return 0;
}