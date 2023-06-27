#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tSampler;


void main()
{
    vec4 imageTexture = texture(tSampler, fragmentUV);
    color = imageTexture * fragmentColor;
}