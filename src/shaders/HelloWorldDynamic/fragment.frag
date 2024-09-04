#version 450

out vec4 FragColor;

in vec3 vertPos;

uniform vec4 color;

void main()
{
    FragColor = vec4(normalize(color.rgb + vertPos), 1.0f);
}