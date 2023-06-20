// Jaidon van Herwaarden May 2023

#include "SudokuSolver.hpp"

#include <imgui.h>

#include <windef.h>
namespace SudokuSolver
{
	void Application::Initialize(const RECT& windowRect)
	{
		_InitializeWindow(windowRect);
		mIsInitialized = true;
	}

	// The main application loop. Returns true when the application wants to close.
	bool Application::Update()
	{
		return false;
	}

	void Application::Render()
	{
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowSize(mWindowSize);
		bool mIsBoardOpen = true;
		ImGui::Begin("Sudoku Board", &mIsBoardOpen, windowFlags);

		mSudokuBoard.RenderBoard();

		ImGui::End();
	}

	void Application::_InitializeWindow(const RECT& windowRect)
	{
		// Size vs. Windows window size is not consistent?
		// X padding = 16
		// Y padding = 40

		mWindowSize.x = static_cast<float>(windowRect.right - windowRect.left)-16.f;
		mWindowSize.y = static_cast<float>(windowRect.bottom - windowRect.top)-40.f;
	}
};