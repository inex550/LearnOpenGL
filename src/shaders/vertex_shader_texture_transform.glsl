#version 400 core

layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec2 attrTexCoords;

out vec3 color;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(attrPos, 1.0);
    color = attrColor;
    texCoords = attrTexCoords;
}