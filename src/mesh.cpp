#include "mesh.h"

int Mesh::getLength() const
{
    return _length;
}

Vector3 Mesh::getVertexColor(int index) const
{
    return _colors[index];
}

Vector3 Mesh::getVertexPosition(int index) const
{
    return _vertices[index];
}


void Mesh::setVertexColor(int index, Vector3 color)
{
    _colors[index] = color;
}

void Mesh::setVertexPosition(int index, Vector3 position)
{
    _vertices[index] = position;
}


Mesh::Mesh(int length)
{
    _length = length;

    _vertices = new Vector3[_length];
    _colors = new Vector3[_length];

    for(int i=0; i<_length; i++)
    {
        float window = i/(float)_length;

        Vector3 vertice;
        vertice.X = genRandFloat(-1.f, 1.f);
        vertice.Y = 0;
        vertice.Z = genRandFloat(-1.f, 1.f);
        _vertices[i] = vertice;
        
        Vector3 color;
        color.X = genRandFloat(-1.f + window, window);
        color.Y = genRandFloat(-1.f + window, window);
        color.Z = genRandFloat(-1.f + window, window);
        _colors[i] = color;
    }
}

Mesh::Mesh(const Mesh& otherMesh)
{

}

Mesh::~Mesh()
{

}