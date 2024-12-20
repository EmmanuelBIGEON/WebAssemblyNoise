#version 300 es
precision highp float;

uniform vec2 resolution;
uniform float time;
out vec4 color;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    color = vec4(uv, 0.0, 1.0);
}
