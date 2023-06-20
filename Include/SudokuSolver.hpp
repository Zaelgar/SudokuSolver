// Jaidon van Herwaarden May 2023
#pragma once

#include <imgui.h>

#include "SudokuBoard.hpp"

#include <windows.h>

namespace SudokuSolver
{

class Application
{
public:
	void Initialize(const RECT& windowRect);

	bool Update();

	void Terminate();
	void Render();

private:
	void _InitializeWindow(const RECT& windowRect);

	bool mIsInitialized = false;

	ImVec2 mPosition;
	ImVec2 mWindowSize;

	SudokuBoard mSudokuBoard;

};

} // namespace SudokuSolver