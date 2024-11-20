#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"

namespace Gameplay
{
	namespace Board
	{
		using namespace Cell;
		using namespace UI::UIElement;
		using namespace Global;
		using namespace Sound;

		BoardController::BoardController()
		{
			board_view = new BoardView(this);
			createBoard();
		}

		BoardController::~BoardController()
		{
			destroy();
		}

		void BoardController::createBoard()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_colums; b++)
				{
					board[a][b] = new CellController(sf::Vector2i(a, b));
				}
			}
		}

		void BoardController::initialize()
		{
			board_view->initialize();
			initializeCells();
			reset();
		}

		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_colums; b++)
				{
					board[a][b]->initialize(cell_width, cell_height);
				}
			}
		}

		void BoardController::update()
		{
			board_view->update();

			for (int row = 0; row < number_of_rows; ++row)
			{
				for (int col = 0; col < number_of_colums; ++col)
				{
					board[row][col]->update();
				}
			}
		}

		void BoardController::render()
		{
			board_view->render();

			for (int row = 0; row < number_of_rows; ++row)
			{
				for (int col = 0; col < number_of_colums; ++col)
				{
					board[row][col]->render();
				}
			}
		}

		void BoardController::reset()
		{
			resetBoard();
			flagged_cells = 0;
		}

		void BoardController::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
		{
			switch (button_type)
			{
			case UI::UIElement::ButtonType::LEFT_MOUSE_BUTTON:
				openCell(cell_controller->getCellPosition());
				break;
			case UI::UIElement::ButtonType::RIGHT_MOUSE_BUTTON:
				flagCell(cell_controller->getCellPosition()); // New Flagging Method - we sue board class now
				break;
			}
		}

		void BoardController::resetBoard()
		{
			for (int row = 0; row < number_of_rows; ++row)
			{
				for (int col = 0; col < number_of_colums; ++col)
				{
					board[row][col]->reset();
				}
			}
		}

		void BoardController::deleteBoard()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_colums; b++)
				{
					delete board[a][b];
				}
			}
		}

		void BoardController::openCell(sf::Vector2i cell_position)
		{
			if (board[cell_position.x][cell_position.y]->canOpenCell())
			{
				board[cell_position.x][cell_position.y]->openCell();
			}
		}

		void BoardController::flagCell(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
			case::Gameplay::Cell::CellState::FLAGGED:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
				flagged_cells--; //Used to update Gameplay UI
				break;
			case::Gameplay::Cell::CellState::HIDDEN:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
				flagged_cells++; //Used to update Gameplay UI
				break;
			}

			board[cell_position.x][cell_position.y]->flagCell();
		}

		int BoardController::getMinesCount()
		{
			//return mines_count;
			return mines_count - flagged_cells;
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete (board_view);
		}
	}
}