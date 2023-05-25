// Jaidon van Herwaarden May 2023
#include "SudokuBoard.hpp"

#include <imgui.h>

namespace SudokuSolver
{
	void SudokuBoard::CollapseValueFromTile(int value, int tileIndex)
	{
		std::set<int> indicesToCollapse = CalculateTileIndicesFromTile(tileIndex);

		for (auto& index : indicesToCollapse)
		{
			mBoard[index].CollapseTile(value);
		}
	}


	/// <summary>
	/// Calculates the indices of the row, column, and local square of the related Sudoku board values
	/// </summary>
	/// <param name="tileIndex">The index of the tile to calculate related tiles indices from</param>
	/// <returns>This returns a set of indices that are related to the tile index (minus the tileIndex itself)</returns>
	std::set<int> SudokuBoard::CalculateTileIndicesFromTile(int tileIndex)
	{
		std::set<int> result;

		// Related column indices
		// Start with lowest number in the column, work our way up
		int startIndex = tileIndex % 9;
		for (int i = startIndex; startIndex < mBoard.size(); i + 9)
		{
			result.insert(i);
		}

		// Related column indices
		// Start from leftmost row index, and add until +9
		startIndex = tileIndex / 9;
		for (int i = startIndex; i < startIndex + 9; ++i)
		{
			result.insert(i);
		}

		// Related local square indices
		// Extract column and row, then get to the smallest index in the square (top left) and add from there
		int row = tileIndex / 9;
		while (row % 3 != 0)
		{
			row--;
		}
		
		int column = tileIndex % 9;
		while (column % 3 != 0)
		{
			--column;
		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				int index = ((row + i) * 9) + (column + j);
				result.insert(index);
			}
		}

		return result;
	}

	void SudokuBoard::RenderBoard()
	{
		struct TextFilters
		{
			// Numbers only
			static int FilterImGuiLetters(ImGuiInputTextCallbackData* data)
			{
				if (data->EventChar < 256 && strchr("123456789", (char)data->EventChar))
					return 0;
				return 1;
			}
		};

		static char buf6[64] = ""; ImGui::InputText("Numbers 1-9 only!", buf6, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);
	}
}