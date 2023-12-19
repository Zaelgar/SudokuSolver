// Jaidon van Herwaarden May 2023
#include "SudokuBoard.hpp"

#include <imgui.h>

namespace SudokuSolver
{
	void SudokuBoard::Initialize(float fontSize)
	{
		ImFontConfig fontConfig;
		fontConfig.SizePixels = fontSize;
		auto io = ImGui::GetIO();
		mDefaultFont = io.Fonts->AddFontDefault();
		mLargeFont = io.Fonts->AddFontDefault(&fontConfig);

		SudokuBoardStyle mInputTextTableStyle{
			9, 9,
			{ 595.f, 0.f },
			{ 13.f, 0.f },
			ImGuiTableFlags_Borders,
			{0.2f, 0.2f, 0.2f, 1.f} }; // dark grey

		mTableStyleInputText = mInputTextTableStyle;

		SudokuBoardStyle tileOutlinesTableStyle{
			3, 3,
			{ 595.f, 0.f },
			{ 13.f, 0.f },
			ImGuiTableFlags_Borders,
			{0.7f, 0.7f, 0.7f, 1.f} }; // light grey

		mTableStyleTileOutlines = mInputTextTableStyle;
	}

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
		for (int i = startIndex; i < mBoard.size(); i += 9)
		{
			result.insert(i);
		}

		// Related row indices
		// Start from leftmost row index, and add until +9
		startIndex = (tileIndex / 9) * 9;
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

	bool SudokuBoard::AreIndicesRelated(int tileIndex1, int tileIndex2)
	{
		std::set<int> results = CalculateTileIndicesFromTile(tileIndex1);
		if (results.contains(tileIndex2))
		{
			return true;
		}
		return false;
	}

	void SudokuBoard::RenderBoard()
	{
		_RenderInputTextTable();
		_RenderTileOutlinesTable();
	}

	void SudokuBoard::_RenderTileOutlinesTable()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, mTableStyleTileOutlines.mTableCellPadding);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, 0); // Make InputTextFields all no-colour (they are not the same size as the cell)
		ImGui::PushStyleColor(ImGuiCol_TableBorderLight, mTableStyleTileOutlines.mTableBorderColour);

		if (ImGui::BeginTable("Sudoku Board", mTableStyleTileOutlines.mSizeX, mTableStyleTileOutlines.mTableFlags, mTableStyleTileOutlines.mMaxTableSize))
		{
			for (int row = 0; row < mTableStyleTileOutlines.mSizeX; row++)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < mTableStyleTileOutlines.mSizeY; column++)
				{
					ImGui::TableNextColumn();
				}
			}
			ImGui::EndTable();
		}


		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
	}

	void SudokuBoard::_RenderInputTextTable()
	{
		ImGui::PushFont(mLargeFont);
		auto TextFilterCallback = [](ImGuiInputTextCallbackData* data) { return (data->EventChar < 256 && strchr("123456789", (char)data->EventChar)) ? 0 : 1; }; // Numbers 1-9 only

		static char buf6[2] = ""; // Number + '\0'
		ImGui::InputText("Numbers 1-9 only!", buf6, 2, ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_AlwaysOverwrite | ImGuiInputTextFlags_AutoSelectAll, TextFilterCallback);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, mTableStyleInputText.mTableCellPadding);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, 0); // Make InputTextFields all no-colour (they are not the same size as the cell)

		ImU32 colour2 = ImGui::GetColorU32(ImVec4(0.f, 0.f, 0.f, 0.65f));
		ImU32 colour1 = ImGui::GetColorU32(ImVec4(0.1f, 0.2f, 0.35f, 0.5f));

		ImGui::PushStyleColor(ImGuiCol_TableBorderLight, mTableStyleInputText.mTableBorderColour);
		const int selectedIndex = 6 + (3 * 9);
		if (ImGui::BeginTable("Sudoku Board", mTableStyleInputText.mSizeX, mTableStyleInputText.mTableFlags, mTableStyleInputText.mMaxTableSize))
		{
			for (int row = 0; row < mTableStyleInputText.mSizeX; row++)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < mTableStyleInputText.mSizeY; column++)
				{
					ImGui::TableNextColumn();

					bool areIndicesRelated = AreIndicesRelated(selectedIndex, (row * mTableStyleInputText.mSizeX) + column);
					if (areIndicesRelated)
					{
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, colour1);
					}
					else
					{
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, colour2);
					}

					ImGui::SetNextItemWidth(-FLT_MIN); // Align to center?
					ImGui::InputText("", buf6, 2, ImGuiInputTextFlags_AlwaysOverwrite | ImGuiInputTextFlags_AutoSelectAll);
				}
			}
			ImGui::EndTable();
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopFont();
	}
}