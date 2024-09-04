#pragma once

#include "framework/module.hpp"
#include "framework/shader.hpp"
#include "cmath"

// Same as HelloWorld module except for the fragment shader
class HelloWorldDynamic : public Module<HelloWorldDynamic>
{
    public:
    HelloWorldDynamic()
    {
        _shader = Shader("./src/shaders/HelloWorldDynamic/vertex.vert", "./src/shaders/HelloWorldDynamic/fragment.frag");
    }

    void StartUp()
    {
        _nVertices = 12;
        _nIndeces = 6;
        _nElements = 1;

        _vertices = new float[_nVertices]{
           -0.5f,   0.5f,   0.0f, // top left
            0.5f,   0.5f,   0.0f, // top right
            0.5f,  -0.5f,   0.0f, // bottom right
           -0.5f,  -0.5f,   0.0f // bottom left
        };
        
        _indeces = new unsigned int[_nIndeces]{
            0, 1, 3,
            1, 2, 3
        };
        
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices , _vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * _nIndeces, _indeces, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
        glEnableVertexAttribArray(0);


        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Update()
    {
         float time = glfwGetTime();
        _shader.Use();
        _shader.SetUniform("color", ImVec4(sinf(time*0.25)*0.5f+0.5, -sinf(time)*0.5f+0.5, sinf(time*0.5)*0.5f+0.5, 1.f));
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _nIndeces, GL_UNSIGNED_INT, 0);
    }

    private:
    Shader _shader;
    unsigned int _VBO, _VAO, _EBO, _nVertices, _nIndeces, _nElements;
    float* _vertices;
    unsigned int* _indeces;
};