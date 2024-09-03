#include "guiApplication.hpp"


using namespace ImGui;

// Use Nvidia dedicated GPU
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
    
int main()
{
    GuiApplication app;

    app.Run();

    return 0;
}
