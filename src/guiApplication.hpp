#pragma once

#include "framework/application.hpp"
#include "applications/HelloWorld.hpp"

class GuiApplication : public Application<GuiApplication>
{
    public:
    void StartUp()
    {
        _isWireframe = false;
        _helloWorldApp.StartUp();
    }

    void Update()
    {
        using namespace ImGui;

        SetNextWindowSize(ImVec2(-1, GetSize().y));
        SetNextWindowPos(ImVec2(0.f, 0.f));
        PushStyleColor(ImGuiCol_WindowBg, ImVec4(.5, .5, .5, 0));
        PushStyleColor(ImGuiCol_ChildBg, ImVec4(.5, .5, .5, 0));
        Begin("GUI Application", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            Checkbox("Render as wireframe", &_isWireframe);
            // Application options
            BeginChild("Options", ImVec2(GetSize().x * .25, 0));
                if(Button("Hello World"))
                    Select(&_helloWorldApp);

            EndChild();

            SameLine();
            BeginChild("Renderer", ImVec2(-10, -1));
                if(IsSelected(&_helloWorldApp))
                {
                    if(_isWireframe)
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                    ImVec2 pos = GetCursorScreenPos();
                    ImVec2 size = GetContentRegionAvail();

                    _helloWorldApp.SetViewport(ImVec4(pos.x, pos.y, size.x, size.y));
                    _helloWorldApp.Update();

                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            EndChild();
        End();
        PopStyleColor(2);
    }

    private:
    HelloWorld _helloWorldApp;
    size_t _selected;
    bool _isWireframe;

    bool IsSelected(void* ref)
    {
        return _selected == reinterpret_cast<size_t>(ref);
    }

    void Select(void* ref)
    {
        _selected = reinterpret_cast<size_t>(ref);
    }
};