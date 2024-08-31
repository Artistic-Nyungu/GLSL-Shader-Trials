#version 450

out vec4 FragColor;

in vec3 vertPos;

void main()
{
    FragColor = vec4(vertPos, 1.0f);
}