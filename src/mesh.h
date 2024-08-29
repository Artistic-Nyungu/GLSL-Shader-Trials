#pragma once

#include "helpers.h"

class Mesh
{
    private:
    Vector3* _vertices;
    Vector3* _colors;
    int _length;

    // OpenGL objects
    unsigned int* VBOs;   // Vertex buffer objects i.e GL_ARRAY_BUFFER

    public:
    int getLength() const;
    Vector3 getVertexColor(int index) const;
    Vector3 getVertexPosition(int index) const;
    
    void setVertexColor(int index, Vector3 color);
    void setVertexPosition(int index, Vector3 color);

    Mesh(int length);
    Mesh(const Mesh& otherMesh);
    ~Mesh();
};

