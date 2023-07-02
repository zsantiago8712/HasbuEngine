#include "imgui.h"

namespace Hasbu::Panels {

void debugPanel(float* ambient, float* diffuse, float* specular, const float deltaTime)
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("HasbuEngine!"); // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)


    // if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
    // counter++;
    //

    // ImGui::SameLine();

    ImGui::ColorEdit3("Ambient color", ambient); // Edit 3 floats representing a color
    ImGui::ColorEdit3("Diffuse color", diffuse); // Edit 3 floats representing a color
    ImGui::ColorEdit3("Specular", specular); // Edit 3 floats representing a color


    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("MainEngine avarge %.3f ms/frame (%.1f FPS)", 1000.0f * deltaTime, 1.0f / deltaTime);
    ImGui::End();
}

}
