#pragma once

#include "framework/application.hpp"
#include "modules/helloWorld.hpp"
#include "modules/helloWorldDynamic.hpp"
#include "modules/textures.hpp"

class GuiApplication : public Application<GuiApplication>
{
    public:
    void StartUp()
    {
        _isWireframe = false;
        _selected = 0;

        // Start up the modules
        _helloWorldModule.StartUp();
        _helloWorldDynamicModule.StartUp();
        _texturesModule.StartUp();
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

            // Create options for selecting the modules
            BeginChild("Options", ImVec2(GetSize().x * .25, 0));
                if(Button("Hello World"))
                    Select(&_helloWorldModule);
                if(Button("Hello World Dynamic"))
                    Select(&_helloWorldDynamicModule);
                if(Button("Textures"))
                    Select(&_texturesModule);

            EndChild();

            SameLine();
            BeginChild("Renderer", ImVec2(-10, -1));
                if(_selected != 0)
                {
                    if(_isWireframe)
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                    ImVec2 pos = GetCursorScreenPos();
                    ImVec2 size = GetContentRegionAvail();

                    if(IsSelected(&_helloWorldModule))
                    {
                        _helloWorldModule.SetViewport(ImVec4(pos.x, pos.y, size.x, size.y));
                        _helloWorldModule.Update();
                    }
                    else if(IsSelected(&_helloWorldDynamicModule))
                    {
                        _helloWorldDynamicModule.SetViewport(ImVec4(pos.x, pos.y, size.x, size.y));
                        _helloWorldDynamicModule.Update();
                    }else if(IsSelected(&_texturesModule))
                    {
                        _texturesModule.SetViewport(ImVec4(pos.x, pos.y, size.x, size.y));
                        _texturesModule.Update();
                    }

                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            EndChild();
        End();
        PopStyleColor(2);
    }

    private:
    size_t _selected;
    bool _isWireframe;

    // Modules
    HelloWorld _helloWorldModule;
    HelloWorldDynamic _helloWorldDynamicModule;
    Textures _texturesModule;

    bool IsSelected(void* ref)
    {
        return _selected == reinterpret_cast<size_t>(ref);
    }

    void Select(void* ref)
    {
        _selected = reinterpret_cast<size_t>(ref);
    }
};