// Jaidon van Herwaarden June 2023

#include "ApplicationState.hpp"
#include "SudokuBoard.hpp"

#include <Windows.h>

#include <imgui.h>

class Application;

class SudokuSolverState : public ApplicationState
{
public:
	void Initialize(const Application* const) override;
	void Terminate() override;

	bool Update() override;
	void Render() override;

private:
	const Application* mApplication = nullptr;

	bool mIsInitialized = false;

	ImVec2 mPosition;
	ImVec2 mWindowSize;

	SudokuSolver::SudokuBoard mSudokuBoard;
};