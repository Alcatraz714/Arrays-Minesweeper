#pragma once
#include "../../header/UI/UIElement/ButtonView.h"

namespace Gameplay
{
    namespace Cell
    {
        class CellController;

        class CellView
        {
        private:
            const float cell_top_offset = 274.f;
            const float cell_left_offset = 583.f;

            const float cell_texture_width = 384;
            const float cell_texture_height = 32;

            const int tile_size = 32;
            const int slice_count = 12;

            UI::UIElement::ButtonView* cell_button;
            CellController* cell_controller;

            void initializeButtonImage(float width, float height);
            sf::Vector2f getCellScreenPosition(float width, float height);
            void setCellTexture();
            void registerButtonCallback();
            void cellButtonCallback(UI::UIElement::ButtonType button_type);

        public:
            CellView(CellController* controller);
            ~CellView();

            void initialize(float width, float height);
            void update();
            void render();
        };
    }
}