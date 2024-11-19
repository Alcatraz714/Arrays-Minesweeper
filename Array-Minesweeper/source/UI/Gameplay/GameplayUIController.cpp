#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Main/GameService.h"
#include <sstream>
#include <iomanip>

namespace UI
{
    namespace GameplayUI
    {
        using namespace Main;
        using namespace Sound;
        using namespace UIElement;
        using namespace Global;

        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
        }

        void GameplayUIController::createButton()
        {
            restart_button = new ButtonView();
        }

        void GameplayUIController::createTexts()
        {
            mine_text = new TextView();
            time_text = new TextView();
        }

        void GameplayUIController::initializeButton()
        {
            restart_button->initialize("Restart Button",
                Config::restart_button_texture_path,
                button_width, button_height,
                sf::Vector2f(restart_button_left_offset, restart_button_top_offset));

            registerButtonCallback();
        }

        void GameplayUIController::initializeTexts()
        {
            initializeMineText();
            initializeTimeText();
        }

        void GameplayUIController::initializeMineText()
        {
            mine_text->initialize("000", sf::Vector2f(mine_text_left_offset, mine_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::initializeTimeText()
        {
            time_text->initialize("000", sf::Vector2f(time_text_left_offset, time_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::update()
        {
            restart_button->update();
            updateMineText();
            updateTimeText();
        }

        void GameplayUIController::render()
        {
            restart_button->render();
            mine_text->render();
            time_text->render();
        }

        void GameplayUIController::show()
        {
            restart_button->show();
            mine_text->show();
            time_text->show();
        }

        void GameplayUIController::updateMineText()
        {
            int mines_count = ServiceLocator::getInstance()->getGameplayService()->getMinesCount();

            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << mines_count;
            std::string string_mine_count = stream.str();

            mine_text->setText(string_mine_count);
            mine_text->update();
        }

        void GameplayUIController::updateTimeText()
        {
            int remaining_time = ServiceLocator::getInstance()->getGameplayService()->getRemainingTime();

            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << remaining_time;
            std::string string_remaining_time = stream.str();

            time_text->setText(string_remaining_time);
            time_text->update();
        }

        void GameplayUIController::restartButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getGameplayService()->startGame();
        }

        void GameplayUIController::registerButtonCallback()
        {
            restart_button->registerCallbackFuntion(std::bind(&GameplayUIController::restartButtonCallback, this));
        }

        void GameplayUIController::destroy()
        {
            delete (restart_button);
            delete (mine_text);
            delete (time_text);
        }
    }
}