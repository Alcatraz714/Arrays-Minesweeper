#include "../../header/Gameplay/Cell/CellModel.h"

namespace Gameplay
{
	namespace Cell
	{
		CellModel::CellModel(sf::Vector2i grid_position)
		{
			reset();
			position = grid_position;
		}

		CellModel::~CellModel() = default;

		CellState CellModel::getCellState()
		{
			return cell_state;
		}

		void CellModel::setCellState(CellState state)
		{
			cell_state = state;
		}

		CellType CellModel::getCellType()
		{
			return cell_type;
		}

		void CellModel::setCellType(CellType type)
		{
			cell_type = type;
		}

		sf::Vector2i CellModel::getCellPosition()
		{
			return position;
		}

		void CellModel::setCellPosition(sf::Vector2i grid_position)
		{
			position = grid_position;
		}

		int CellModel::getMinesAround()
		{
			return mines_around;
		}

		void CellModel::setMinesAround(int mine_count)
		{
			mines_around = mine_count;
		}

		void CellModel::reset()
		{
			cell_state = CellState::HIDDEN;
			cell_type = CellType::EMPTY;
			mines_around = 0;
		}
	}
}