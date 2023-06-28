#include "imgui.h"

namespace Hasbu::Panels {

void debugPanel(float* colors, const float deltaTime, float& ambient, float& specular, int& iluminationSelected)
{
    static bool ambientSelect = true;
    static bool diffuseSelect = false;
    static bool specularSelect = false;

    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("HasbuEngine!"); // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

    if (ImGui::Checkbox("Ambient Ilumination", &ambientSelect)) {
        diffuseSelect = false;
        specularSelect = false;
        iluminationSelected = 0;
    }

    if (ImGui::Checkbox("Diffuse Ilumination", &diffuseSelect)) {
        ambientSelect = false;
        specularSelect = false;
        iluminationSelected = 1;
    }

    if (ImGui::Checkbox("Specular Ilumination", &specularSelect)) {
        ambientSelect = false;
        diffuseSelect = false;
        iluminationSelected = 2;
    }

    ImGui::SliderFloat("Ambiength Strength", &ambient, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("Specular Strength", &specular, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

    // if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
    // counter++;
    //

    // ImGui::SameLine();

    ImGui::ColorEdit3("Cube Color", colors); // Edit 3 floats representing a color

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("MainEngine avarge %.3f ms/frame (%.1f FPS)", 1000.0f * deltaTime, 1.0f / deltaTime);
    ImGui::End();
}

}
