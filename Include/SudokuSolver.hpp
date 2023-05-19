// Jaidon van Herwaarden May 2023
#pragma once

#include <imgui.h>

namespace SudokuSolver
{

class Application
{
public:
	Application() = delete;
	Application(ImGuiIO& io);

	bool Update();

	void Terminate();
	void Render();

private:
	ImGuiIO& mIO;
};

} // namespace SudokuSolver