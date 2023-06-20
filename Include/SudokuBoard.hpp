// Jaidon van Herwaarden May 2023
#pragma once

#include <array>
#include <set>


#include "Tile.hpp"

namespace SudokuSolver
{

class SudokuBoard
{
public:
	SudokuBoard() = default;

	void CollapseValueFromTile(int value, int tileIndex);
	void RenderBoard();

private:

	std::set<int> CalculateTileIndicesFromTile(int tileIndex);

	std::array<Tile, 81> mBoard;

	bool mIsBoardOpen = true;
};

}