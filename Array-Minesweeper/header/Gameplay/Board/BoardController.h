#pragma once
#include <sfml/Graphics.hpp>
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <random>

namespace Gameplay
{
    namespace Board
    {
        class BoardView;

        class BoardController
        {
        public:
            static const int number_of_rows = 9;
            static const int number_of_colums = 9;
            static const int mines_count = 8;
            

            BoardController();
            ~BoardController();

            void initialize();
            void update();
            void render();
            void reset();
            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

        private:
            BoardView* board_view;
            Cell::CellController* board[number_of_rows][number_of_colums];

            void createBoard();
            void initializeCells();
            void destroy();
            void resetBoard();
            void deleteBoard();
            //Cell functions
            void openCell(sf::Vector2i cell_position);
            void flagCell(sf::Vector2i cell_position);
            int flagged_cells;

            int getMinesCount();
            
        };
    }
}