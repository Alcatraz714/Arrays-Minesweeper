#pragma once
#include <sfml/Graphics.hpp>

namespace Gameplay
{
    namespace Cell
    {
        class CellView;
        class CellModel;
        enum class CellState;
        enum class CellType;

        class CellController
        {
        private:
            CellView* cell_view;
            CellModel* cell_model;

            void destroy();

        public:
            CellController(sf::Vector2i grid_position);
            ~CellController();

            void initialize(float cell_width, float cell_height);
            void update();
            void render();

            void flagCell();
            void openCell();
            bool canOpenCell();

            CellState getCellState();
            void setCellState(CellState state);
            CellType getCellType();
            void setCellType(CellType type);
            sf::Vector2i getCellPosition();
            int getMinesAround();

            void reset();
        };
    }
}