// Jaidon van Herwaarden May 2023
#pragma once

#include <array>
#include <set>

#include "imgui.h"

#include "Tile.hpp"

namespace SudokuSolver
{
	class SudokuBoard
	{
	public:
		struct SudokuBoardStyle
		{
			SudokuBoardStyle() = default;
			SudokuBoardStyle(int sizeX, int sizeY, ImVec2 maxTableSize, ImVec2 cellPadding, ImGuiTableFlags tableFlags, ImVec4 tableBorderColour)
				: mSizeX(sizeX)
				, mSizeY(sizeY)
				, mMaxTableSize(595.f, 0.f)
				, mTableCellPadding(13.f, 0.f)
				, mTableFlags(ImGuiTableFlags_Borders)
				, mTableBorderColour(ImGui::GetColorU32(tableBorderColour))
			{}

			int mSizeX = 9;
			int mSizeY = 9;
			ImVec2 mMaxTableSize = { 595.f, 0.f };
			ImVec2 mTableCellPadding = { 13.f, 0.f };
			ImGuiTableFlags mTableFlags = ImGuiTableFlags_Borders;
			ImU32 mTableBorderColour = INTMAX_MAX; // Should be white??
		};


		SudokuBoard() = default;

		void Initialize(float fontSize = 13.f);
		void CollapseValueFromTile(int value, int tileIndex);
		void RenderBoard();

		bool AreIndicesRelated(int tileIndex1, int tileIndex2);

		ImFont* mLargeFont;
		ImFont* mDefaultFont;

	private:
		void _RenderTileOutlinesTable();
		void _RenderInputTextTable();

		std::array<Tile, 81> mBoard;
		std::set<int> CalculateTileIndicesFromTile(int tileIndex);

		SudokuBoardStyle mTableStyleInputText; // dark grey
		SudokuBoardStyle mTableStyleTileOutlines; // light grey

		bool mIsBoardOpen = true;
	};
}