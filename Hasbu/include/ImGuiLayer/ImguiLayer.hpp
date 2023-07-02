#pragma once







namespace Hasbu::Gui {



struct ImGuiLayer {

    static void create();
    
    static void begin();

    static void render();

    static void clear();

    static bool wantCaptureMouse();
    static bool wantCaptureKeyboard();


};




}
