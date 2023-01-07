#version 400 core

struct Material {
    sampler2D texture_diffuse0;
};

struct DirLight {
    vec3 direction;

    vec3 color;
};

uniform Material material;
uniform DirLight light;

in vec3 fragPos;
in vec3 normal;
in vec2 texPos;

out vec4 fragColor;

vec3 computeDirLight(DirLight light, vec3 norm) {
    vec3 lightDir = normalize(light.direction);

    float diff = max(dot(lightDir, norm), 0.2);
    vec3 diffuse = diff * light.color * vec3(texture(material.texture_diffuse0, texPos));

    return diffuse;
}

void main() {
    vec3 norm = normalize(normal);

    fragColor = vec4(computeDirLight(light, norm), 1.0);
}