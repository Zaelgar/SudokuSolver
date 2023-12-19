// Jaidon van Herwaarden May 2023

#include "SudokuSolverState.hpp"
#include "Application.hpp"

#include <imgui.h>
#include <windef.h>

void SudokuSolverState::Initialize(const Application* const application)
{
	mApplication = application;
	ASSERT(mApplication != nullptr, "Invalid application pointer");
	mWindowSize = application->GetWindowSize();
	mWindowSize.x -= 16.f;
	mWindowSize.y -= 39.f;

	mSudokuBoard.Initialize(45.f);

	mIsInitialized = true;
}

// The main application loop. Returns true when the application wants to close.
bool SudokuSolverState::Update()
{
	return false;
}

void SudokuSolverState::Render()
{
	if (false)
	{
		ImGui::ShowDemoWindow();
	}
	else
	{
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
		ImGui::SetNextWindowSize(mWindowSize);
		bool mIsBoardOpen = true;
		ImGui::Begin("Sudoku Board", &mIsBoardOpen, windowFlags);

		mSudokuBoard.RenderBoard();

		ImGui::End();
	}
}

void SudokuSolverState::Terminate()
{

}