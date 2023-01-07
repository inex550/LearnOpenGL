#version 400 core

struct Material {
    sampler2D diffuseTex;
    sampler2D specularTex;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 objColor;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 fragPos;
in vec2 texPos;

out vec4 fragColor;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 ambient = light.ambient * vec3(texture(material.diffuseTex, texPos));

    float diff = max(dot(lightDir, norm), 0.0);
    diff = min(diff, 1.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTex, texPos));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specularTex, texPos));

    fragColor = vec4((ambient + diffuse + specular) * objColor, 1.0);
}