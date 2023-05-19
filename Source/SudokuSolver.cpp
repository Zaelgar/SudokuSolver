#include "SudokuSolver.hpp"

#include <imgui.h>
namespace SudokuSolver
{
Application::Application(ImGuiIO& io)
    :mIO(io)
{}

// The main application loop. Returns true when the application wants to close.
bool Application::Update()
{
    static bool show = true;
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Sudoku Solver");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too    

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / mIO.Framerate, mIO.Framerate);
    ImGui::End();

    return false;
}

};