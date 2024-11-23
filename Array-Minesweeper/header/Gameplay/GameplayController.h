#pragma once
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    using namespace Gameplay::Board;

    enum class GameResult
    {
        NONE,
        WON,
        LOST
    };

    class GameplayController
    {
    private:
        const float max_level_duration = 301.0f;
        const float game_over_time = 11.f;
        BoardService* board_service;

        float remaining_time;
        GameResult game_result;

        void updateRemainingTime();
        bool isTimeOver();
        void showCredits();;
        void beginGameOverTimer();

        void gameWon();
        void gameLost();

    public:
        ~GameplayController();

        void initialize();
        void update();
        void render();

        void restart();
        void endGame(GameResult result);

        int getMinesCount();
        float getRemainingTime();
    };
}