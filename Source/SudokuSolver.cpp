// Jaidon van Herwaarden May 2023

#include "SudokuSolver.hpp"

#include <imgui.h>
namespace SudokuSolver
{
	// The main application loop. Returns true when the application wants to close.
	bool Application::Update()
	{
		Render();

		return false;
	}

	void Application::Render()
	{
		ImGuiIO imguiIO = ImGui::GetIO();
		imguiIO.DisplaySize.x = 1280;
		imguiIO.DisplaySize.y = 800;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		ImVec2 position{ 150, 150 };
		ImVec2 windowSize{ 1000, 600 };
		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowSize(windowSize);

		bool mIsBoardOpen = true;
		ImGui::Begin("Sudoku Board", &mIsBoardOpen, windowFlags);

		mSudokuBoard.RenderBoard();

		ImGui::End();
	}

};