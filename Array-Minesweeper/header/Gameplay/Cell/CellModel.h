#pragma once
#include <sfml/Graphics.hpp>

namespace Gameplay
{
    namespace Cell
    {
        enum class CellState
        {
            HIDDEN,
            OPEN,
            FLAGGED,
        };

        enum class CellType
        {
            EMPTY,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            MINE,
        };

        class CellModel
        {
        private:
            CellState cell_state;
            CellType cell_type;

            sf::Vector2i position;
            int mines_around;

        public:
            CellModel(sf::Vector2i grid_position);
            ~CellModel();

            CellState getCellState();
            void setCellState(CellState state);

            CellType getCellType();
            void setCellType(CellType type);

            sf::Vector2i getCellPosition();
            void setCellPosition(sf::Vector2i grid_position);

            int getMinesAround();
            void setMinesAround(int mine_count);

            void reset();
        };
    }
}