#version 400 core

in vec3 color;
in vec2 texCoords;

out vec4 fg_color;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixAmount;

void main() {
    fg_color = mix(
        texture(texture1, texCoords),
        texture(texture2, texCoords), mixAmount
    ) * vec4(color, 1.0);
}