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
		ImGui::PushFont(mLargeFont);
		auto TextFilterCallback = [](ImGuiInputTextCallbackData* data) { return (data->EventChar < 256 && strchr("123456789", (char)data->EventChar)) ? 0 : 1; }; // Numbers 1-9 only

		static char buf6[2] = ""; // Number + '\0'
		ImGui::InputText("Numbers 1-9 only!", buf6, 2, ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_AlwaysOverwrite | ImGuiInputTextFlags_AutoSelectAll, TextFilterCallback);

		static float minCellSize = 50.f;
		ImGui::SliderFloat("minCellSize", &minCellSize, -10.f, 1000.f);

		static ImVec2 maxTableSize{ 450.f, 450.f };
		ImGui::SliderFloat2("maxTableSize", &maxTableSize.x, 0, 2000.f);

		static ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders;

		ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &tableFlags, ImGuiTableFlags_RowBg);
		ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &tableFlags, ImGuiTableFlags_Borders);

		static ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_None;
		ImGui::CheckboxFlags("ImGuiTableColumnFlags_WidthFixed", &tableFlags, ImGuiTableColumnFlags_WidthFixed);

		//ImGui::ShowStyleEditor();

		static ImVec2 cellPadding = { 8.f,0.f };
		ImGui::SliderFloat2("cellPadding", &cellPadding.x, 0.f, 100.f);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cellPadding); // Cell padding of {8.f, 0.f} works for 45.f font input text field
		ImGui::PushStyleColor(ImGuiCol_FrameBg, 0); // Make InputTextFields all no-colour (they are not the same size as the cell)

		ImU32 colour1 = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
		ImU32 colour2 = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.7f, 0.65f));


		const int selectedIndex = 4 + (2 * 9);
		if (ImGui::BeginTable("Sudoku Board", 9, tableFlags, maxTableSize))
		{
			for (int row = 0; row < 9; row++)
			{
				ImGui::TableNextRow(0, minCellSize);
				for (int column = 0; column < 9; column++)
				{
					ImGui::TableNextColumn();

					if (AreIndicesRelated(selectedIndex, (row * 9) + column))
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, colour1);
					else
						ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, colour2);

					ImGui::SetNextItemWidth(-FLT_MIN); // Align to center?
					ImGui::InputText("", buf6, 2, ImGuiInputTextFlags_AlwaysOverwrite | ImGuiInputTextFlags_AutoSelectAll);
				}
			}
			ImGui::EndTable();
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopFont();
	}
}