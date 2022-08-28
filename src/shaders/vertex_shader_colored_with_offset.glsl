#version 400 core

layout (location = 0) in vec3 layoutPos;
layout (location = 1) in vec3 layoutColor;

out vec3 color;

uniform float offset;

void main() {
    gl_Position = vec4(layoutPos.x + offset, layoutPos.yz, 1.0);
    color = layoutColor;
}