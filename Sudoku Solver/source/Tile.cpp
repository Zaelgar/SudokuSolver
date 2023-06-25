// Jaidon van Herwaarden May 2023
#include "Tile.hpp"

namespace SudokuSolver
{

	Tile::Tile()
	{
		Reset();
	}

	bool Tile::CollapseTile(int value)
	{
		return static_cast<bool>(mAvailableValues.erase(value));
	}

	void Tile::Reset()
	{
		mAvailableValues.clear();
		for (int i = 1; i <= 9; ++i)
		{
			mAvailableValues.insert(i);
		}
	}

	bool Tile::operator<(const Tile& other)
	{
		return mAvailableValues.size() < other.GetEntropy();
	}

} // namespace SudokuSolver