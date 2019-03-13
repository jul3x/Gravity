//
// Created by jprolejko on 26.02.19.
//

#include <Engine.h>

int main()
{
    constexpr int FRAME_RATE = 30;

    Engine::getInstance().update(FRAME_RATE);

    return 0;
}