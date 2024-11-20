#pragma once
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"


namespace Gameplay
{
    namespace Board
    {
        using namespace Cell;
        using namespace UI::UIElement;
        class BoardService
        {
        private:
            Board::BoardController* board_controller;

            void destroy();

        public:
            BoardService();
            ~BoardService();
            void initialize();
            void update();
            void render();

            int getMinesCount();

            void resetBoard();
            void processCellInput(CellController* cell_controller, ButtonType button_type);
        };
    }
}