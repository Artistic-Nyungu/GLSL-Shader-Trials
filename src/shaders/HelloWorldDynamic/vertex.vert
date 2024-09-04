#version 450

layout (location=0) in vec3 aPos;

out vec3 vertPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);

    vertPos = (aPos * 0.5 + 0.5).yxy;
}