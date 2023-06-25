// Jaidon van Herwaarden June 2023

#include <Windows.h>
#include <Application.hpp>
#include <SudokuSolverState.hpp>

// Main code
int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCommandLine, _In_ int nShowCMD)
{
	Application SudokuSolver;
	SudokuSolver.AddState<SudokuSolverState>({"SudokuSolverState"});

	AppConfig SudokuSolverConfig{ L"Sudoku Solver", 800, 600 };
	SudokuSolver.Run(SudokuSolverConfig);

	return 0;
}