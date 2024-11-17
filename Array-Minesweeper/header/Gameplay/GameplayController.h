#pragma once
#include "../../header/Gameplay/Board/BoardController.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    class GameplayController
    {
    private:
        const float max_level_duration = 301.f;

        float remaining_time;

        void updateRemainingTime();

    public:
        GameplayController();
        ~GameplayController();

        void initialize();
        void update();
        void render();

        void restart();
        int getMinesCount();
        float getRemainingTime();
    };
}