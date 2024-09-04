#version 450

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, texCoord) * vec4(color, .25f);
}