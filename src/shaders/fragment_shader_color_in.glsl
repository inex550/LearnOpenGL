#version 400 core

out vec4 fg_color;

in vec3 color;

void main() {
    fg_color = vec4(color, 1.0);
}