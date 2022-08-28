#version 400 core

layout (location = 0) in vec3 layoutPos;
layout (location = 2) in vec3 layoutColor;

out vec3 color;

void main() {
    gl_Position = vec4(layoutPos, 1.0);
    color = layoutColor;
}