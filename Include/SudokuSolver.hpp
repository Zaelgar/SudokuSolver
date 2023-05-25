// Jaidon van Herwaarden May 2023
#pragma once

#include <imgui.h>
#include "SudokuBoard.hpp"

namespace SudokuSolver
{

class Application
{
public:
	bool Update();

	void Terminate();
	void Render();

private:
	SudokuBoard mSudokuBoard;

};

} // namespace SudokuSolver