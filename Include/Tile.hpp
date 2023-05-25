// Jaidon van Herwaarden May 2023
#pragma once

#include <set>

namespace SudokuSolver
{

class Tile
{
public:
	Tile();

	bool CollapseTile(int value);
	void Reset();

	int GetEntropy() const { return mAvailableValues.size(); }

	bool operator<(const Tile& a);

private:
	std::set<int> mAvailableValues;
};

}