#pragma once

#include "framework/application.hpp"

template<typename Derived>
class Module
{
    public:
    void StartUp()
    {
        static_cast<Derived*>(this)->StartUp();
    }

    void Update()
    {
        static_cast<Derived*>(this)->Update();
    }

    ~Module()
    {
        
    }

    ImVec4 GetViewport()
    {
        int dims[4] = {0};

        glGetIntegerv(GL_VIEWPORT, dims);

        return ImVec4(dims[0], dims[1], dims[2], dims[3]);
    }

    void SetViewport(ImVec4 dims)
    {
        glViewport((int)dims.x, (int)dims.y, (int)dims.z, (int)dims.w);
    }

    protected:
    std::string _name;

    private:
};