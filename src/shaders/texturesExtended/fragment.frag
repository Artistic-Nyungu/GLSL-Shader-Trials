#version 450

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    float linearStrength = length((texCoord.xy - 0.5) * 2);
    float parabolicStrength = smoothstep(0, 1, pow(linearStrength, 2));
    FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), parabolicStrength);
}