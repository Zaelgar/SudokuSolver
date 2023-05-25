#include "pch.h"

#include "Tile.hpp"

TEST(Tile, NewTileMaxEntropyAndAvailableValues)
{
	SudokuSolver::Tile tile;

	EXPECT_EQ(9, tile.GetEntropy());
}

TEST(Tile, CollapseValues)
{
	SudokuSolver::Tile tile;

	EXPECT_TRUE(tile.CollapseTile(1));
	EXPECT_EQ(8, tile.GetEntropy());

	EXPECT_FALSE(tile.CollapseTile(1));
	EXPECT_EQ(8, tile.GetEntropy());
}