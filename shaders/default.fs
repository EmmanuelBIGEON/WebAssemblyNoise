#version 300 es
precision highp float;
in vec2 texCoord;

out vec4 color;

void main()
{
    color = vec4(texCoord.x, texCoord.x, texCoord.x, 1.0);
} 