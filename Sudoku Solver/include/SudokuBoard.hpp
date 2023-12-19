// Jaidon van Herwaarden May 2023
#pragma once

#include <array>
#include <set>


#include "Tile.hpp"

struct ImFont;

namespace SudokuSolver
{

class SudokuBoard
{
public:
	SudokuBoard() = default;

	void Initialize(float fontSize = 13.f);
	void CollapseValueFromTile(int value, int tileIndex);
	void RenderBoard();
	
	bool AreIndicesRelated(int tileIndex1, int tileIndex2);

	ImFont* mLargeFont;
	ImFont* mDefaultFont;

private:
	std::set<int> CalculateTileIndicesFromTile(int tileIndex);

	std::array<Tile, 81> mBoard;

	bool mIsBoardOpen = true;	
};

}