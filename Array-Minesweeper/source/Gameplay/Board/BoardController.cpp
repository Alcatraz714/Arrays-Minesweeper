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

		BoardController::BoardController() : random_engine(random_device())
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
			board_state = BoardState::FIRST_CELL; // new addition
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
				//board[cell_position.x][cell_position.y]->openCell(); - old implementation
				if (board_state == BoardState::FIRST_CELL)
				{
					populateBoard(cell_position);
					board_state = BoardState::PLAYING;
				}
				processCellType(cell_position); //Handles different cell value
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

		void BoardController::populateBoard(sf::Vector2i cell_position)
		{
			populateMines(cell_position);
			populateCells();
		}

		void BoardController::populateMines(sf::Vector2i cell_position)
		{
			// Co-ordinate distribution i.e. selecting random position for mines.
			std::uniform_int_distribution<int> x_distribution(0, number_of_colums - 1); //Subtracted -1 because index in an array ranges from 0 to size-1x
			std::uniform_int_distribution<int> y_distribution(0, number_of_rows - 1);

			// Generate mines.
			for (int a = 0; a < mines_count; a++)
			{
				int i = static_cast<int>(x_distribution(random_engine));
				int j = static_cast<int>(y_distribution(random_engine));

				// If the cell is already a mine or it's the same cell that the player wants to open --> Run the loop an extra time
				if (board[i][j]->getCellType() == CellType::MINE || (cell_position.x == i && cell_position.y == j)) a--; //a-- runs a loop 1 extra time
				else board[i][j]->setCellType(CellType::MINE);
			}
		}

		void BoardController::populateCells()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_colums; b++)
				{
					if (board[a][b]->getCellType() != CellType::MINE)
					{
						CellType value = static_cast<CellType>(countMinesAround(sf::Vector2i(a, b)));
						board[a][b]->setCellType(value);
					}
				}
			}
		}

		int BoardController::countMinesAround(sf::Vector2i cell_position)
		{
			int mines_around = 0;

			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					//If its the current cell, or cell position is not valid, then the loop will skip once
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b))) continue;

					if (board[a + cell_position.x][b + cell_position.y]->getCellType() == CellType::MINE) mines_around++;
				}
			}

			return mines_around;
		}

		bool BoardController::isValidCellPosition(sf::Vector2i cell_position)
		{
			// if position is withing the bounds of the array, then position is valid
			return (cell_position.x >= 0 && cell_position.y >= 0 && cell_position.x < number_of_colums && cell_position.y < number_of_rows);
		}

		void BoardController::processCellType(sf::Vector2i cell_position)
		{
			switch (board[cell_position.x][cell_position.y]->getCellType())
			{
			case::Gameplay::Cell::CellType::EMPTY:
				processEmptyCell(cell_position);
				break;
			case::Gameplay::Cell::CellType::MINE:
				//processMineCell(cell_position);
				break;
			default:
				ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
				break;
			}
		}

		void BoardController::openEmptyCells(sf::Vector2i cell_position)
		{
			// Check the state of the cell at the given position.
			switch (board[cell_position.x][cell_position.y]->getCellState())
			{
				// If the cell is already OPEN, no further action is required, and we return from the function.
			case::Gameplay::Cell::CellState::OPEN:
				return;

				// If the cell is FLAGGED, decrement the flagged_cells count as the flag will be removed.
			case::Gameplay::Cell::CellState::FLAGGED:
				flagged_cells--;
				// No break statement here, so the default case will execute next

			// Default case handles the scenario where the cell is neither OPEN nor FLAGGED, which implies it is HIDDEN.
			default:
				// Opens the cell at the current position.
				board[cell_position.x][cell_position.y]->openCell();
			}

			// Iterate over all neighbouring cells.
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					// Skip the iteration if it's the current cell or if the new cell position is not valid.
					if ((a == 0 && b == 0) || !isValidCellPosition(sf::Vector2i(a + cell_position.x, b + cell_position.y)))
						continue;

					// Calculate the position of the neighbouring cell.
					sf::Vector2i next_cell_position = sf::Vector2i(a + cell_position.x, b + cell_position.y);
					// Recursively open the neighbouring cell.
					openCell(next_cell_position);
				}
			}
		}

		void BoardController::processEmptyCell(sf::Vector2i cell_position)
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
			openEmptyCells(cell_position);
		}

		int BoardController::getMinesCount()
		{
			//return mines_count;
			return mines_count - flagged_cells;
		}

		void BoardController::openAllCells()
		{
			if (board_state == BoardState::FIRST_CELL)
			{
				populateBoard(sf::Vector2i(0, 0));
			}

			for (int a = 0; a < number_of_rows; ++a)
			{
				for (int b = 0; b < number_of_colums; ++b)
				{
					board[a][b]->openCell();
				}
			}
		}

		BoardState BoardController::getBoardState()
		{
			return board_state;
		}

		void BoardController::setBoardState(BoardState state)
		{
			board_state = state;
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete (board_view);
		}
	}
}