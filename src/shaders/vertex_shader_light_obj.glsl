#version 400 core

layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrNormal;
layout (location = 2) in vec2 attrTexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

flat out vec3 normal;
out vec3 fragPos;

out vec2 texPos;

void main() {
    gl_Position = projection * view * model * vec4(attrPos, 1.0);
    normal = mat3(transpose(inverse(model))) * attrNormal;
    fragPos = vec3(model * vec4(attrPos, 1.0));
    texPos = attrTexPos;
}