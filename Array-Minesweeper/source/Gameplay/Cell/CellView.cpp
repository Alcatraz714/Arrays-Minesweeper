#include "../../header/Gameplay/Cell/CellView.h"
#include "../../header/Global/Config.h"

namespace Gameplay
{
    namespace Cell
    {
        using namespace UI::UIElement;
        using namespace Global;

        CellView::CellView(CellController* controller)
        {
            cell_controller = controller;
            cell_button = new ButtonView();
        }

        CellView::~CellView() { delete (cell_button); }

        void CellView::initialize()
        {
            initializeButtonImage(tile_size * 3, tile_size * 3);
        }

        void CellView::initializeButtonImage(float width, float height)
        {
            cell_button->initialize("Cell", Config::cells_texture_path, width, height, sf::Vector2f(0, 0));
        }

        void CellView::update()
        {
            cell_button->update();
        }

        void CellView::render()
        {
            cell_button->render();
        }
    }
}