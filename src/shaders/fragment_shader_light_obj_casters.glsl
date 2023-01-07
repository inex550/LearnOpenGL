#version 400 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct DirLight {
    vec3 direction;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;
};

struct FlashLight {
    vec3 position;
    vec3 direction;

    vec3 color;

    float angle;
    float outerAngle;

    float power;
};

uniform vec3 ambientStrength;
uniform vec3 diffuseStrength;
uniform vec3 specularStrength;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform FlashLight flashlight;

uniform vec3 viewPos;

in vec3 fragPos;
flat in vec3 normal;
in vec2 texPos;

out vec4 fragColor;

vec3 computeDirLight(DirLight light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 ambient = ambientStrength * vec3(texture(material.diffuse, texPos));

    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diffuseStrength * diff * vec3(texture(material.diffuse, texPos));

    float spec = max(dot(reflectDir, viewDir), 0.0);
    vec3 specular = specularStrength * spec * vec3(texture(material.specular, texPos));

    return ambient + diffuse + specular;
}

vec3 computePointLight(PointLight light, vec3 norm, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist);

    vec3 ambient = ambientStrength * vec3(texture(material.diffuse, texPos));

    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diffuseStrength * diff * vec3(texture(material.diffuse, texPos));

    float spec = max(dot(reflectDir, viewDir), 0.0);
    vec3 specular = specularStrength * spec * vec3(texture(material.specular, texPos));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 computeFlashLight(FlashLight light) {
    vec3 flashlightDir = normalize(light.position - fragPos);

    vec3 result = vec3(0.0);

    float angle = dot(-light.direction, flashlightDir);
    if (angle > light.outerAngle) {
        float flashPower = clamp((angle - light.outerAngle) / (light.angle - light.outerAngle), 0.0, 1.0);
        result = vec3(texture(material.diffuse, texPos)) * flashPower * light.power;
    }

    return result;
}

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = vec3(0.0);

    result += computeDirLight(dirLight, norm, viewDir);
    result += computePointLight(pointLight, norm, viewDir);
    result += computeFlashLight(flashlight);

    result = clamp(result, 0.0, 1.0);

    fragColor = vec4(result, 1.0);
}