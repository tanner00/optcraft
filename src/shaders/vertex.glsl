#version 330 core

layout(location = 0) in vec3 pos;

uniform float x;

void main() { gl_Position = vec4(pos.x - x, pos.y, pos.z, 1.0f); }