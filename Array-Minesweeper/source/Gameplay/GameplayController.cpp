#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Time/TimeService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Gameplay
{
    using namespace Main;
    using namespace Board;
    using namespace Global;
    using namespace Cell;
    using namespace UI::UIElement;
    using namespace Time;

    GameplayController::~GameplayController() { board_service = nullptr; }

    void GameplayController::initialize()
    {
        board_service = ServiceLocator::getInstance()->getBoardService();
    }

    void GameplayController::update()
    {
        updateRemainingTime();

        if (isTimeOver())
            endGame(GameResult::LOST);
    }

    void GameplayController::render() {  }

    void GameplayController::updateRemainingTime()
    {
        if (game_result == GameResult::WON)
            return;
        remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }

    bool GameplayController::isTimeOver() { return (remaining_time <= 1); }

    void GameplayController::restart()
    {
        game_result = GameResult::NONE;
        board_service->resetBoard();
        remaining_time = max_level_duration;
    }

    int GameplayController::getMinesCount() { return board_service->getMinesCount(); }

    float GameplayController::getRemainingTime() { return remaining_time; }

    void GameplayController::endGame(GameResult result)
    {
        switch (result)
        {
        case GameResult::WON:
            gameWon();
            break;
        case GameResult::LOST:
            gameLost();
            break;
        default:
            break;
        }
    }

    void GameplayController::gameWon()
    {
        game_result = GameResult::WON;
        board_service->flagAllMines();
        board_service->setBoardState(BoardState::COMPLETED);
        ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::GAME_WON);
    }

    void GameplayController::gameLost()
    {
        if (game_result == GameResult::NONE)
        {
            game_result = GameResult::LOST;
            beginGameOverTimer();
            board_service->showBoard();
            board_service->setBoardState(BoardState::COMPLETED);
        }
        else
        {
            showCredits();
        }

    }

    void GameplayController::beginGameOverTimer() { remaining_time = game_over_time; }

    void GameplayController::showCredits() { GameService::setGameState(GameState::CREDITS); }
}