#pragma once

#include "framework/module.hpp"
#include "framework/shader.hpp"

// Same as HelloWorld module except for the fragment shader
class TexturesExtended : public Module<TexturesExtended>
{
    public:
    TexturesExtended()
    {
        _shader = Shader("./src/shaders/texturesExtended/vertex.vert", "./src/shaders/texturesExtended/fragment.frag");
    }

    void StartUp()
    {
        _nVertices = 12;
        _nIndeces = 6;
        _nElements = 1;

        int length = (int)(_nVertices * (2.f + 2.f / 3.f));
        _vertices = new float[length]{
           -0.5f,   0.5f,   0.0f, /* top left */        0.f, 0.f, 1.f, /* Blue? */    0.f, 1.f, /* Idk */
            0.5f,   0.5f,   0.0f, /* top right */       1.f, 0.f, 1.f, /* Purple? */  1.f, 1.f, /* Idk */
            0.5f,  -0.5f,   0.0f, /* bottom right */    1.f, 1.f, 0.f, /* Idk */      1.f, 0.f, /* Idk */
           -0.5f,  -0.5f,   0.0f, /* bottom left */     0.f, 1.f, 1.f, /* Blue? */    0.f, 0.f  /* Idk */
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

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length , _vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _nIndeces, _indeces, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        _textures = new unsigned int[2]{
            _shader.GenerateTexture("./textures/ground.jpg", GL_RGB, GL_TEXTURE0),
            _shader.GenerateTexture("./textures/grass.jpg", GL_RGB, GL_TEXTURE1)
        };

        _shader.Use();
        _shader.SetUniform("texture0", 0);
        _shader.SetUniform("texture1", 1);

        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Update()
    {
        _shader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textures[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _textures[1]);

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _nIndeces, GL_UNSIGNED_INT, 0);
    }

    ~TexturesExtended()
    {
        delete[] _vertices;
        delete[] _indeces;
        delete[] _textures;

        _vertices = nullptr;
        _indeces = _textures = nullptr;
    }

    private:
    Shader _shader;
    unsigned int _VBO, _VAO, _EBO, _nVertices, _nIndeces, _nElements;
    float* _vertices;
    unsigned int* _indeces;
    unsigned int* _textures;
};