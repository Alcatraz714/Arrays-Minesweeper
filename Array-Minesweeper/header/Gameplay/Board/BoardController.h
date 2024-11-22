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

        enum class BoardState
        {
            FIRST_CELL,       // The state when the player opens first cell - populate cells after first cell is opened
            PLAYING,          // The game is in progress.
            COMPLETED,        // The game is over.
        };

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

            int getMinesCount();
            void openAllCells();

            BoardState getBoardState();
            void setBoardState(BoardState state);

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

            //Population of cells
            BoardState board_state;
            void populateBoard(sf::Vector2i cell_position);
            void populateMines(sf::Vector2i cell_position);
            void populateCells();
            int countMinesAround(sf::Vector2i cell_position);
            bool isValidCellPosition(sf::Vector2i cell_position);

            // To generate random values.
            std::default_random_engine random_engine;

            // To give random seed to generator.
            std::random_device random_device;
            
        };
    }
}