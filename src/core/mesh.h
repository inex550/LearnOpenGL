#ifndef _MESH_H_
#define _MESH_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "program.h"
#include "types.h"

#include <iostream>
#include <vector>

#define TEX_DIFFUSE 0
#define TEX_SPECULAR 1

struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    std::vector<MeshVertex> vertices;
    std::vector<uint32> indicies;

    Mesh(std::vector<MeshVertex> vertices, std::vector<uint32> indicies);

    void draw(ShaderProgram& program);

private:
    GLuint VAO, VBO, EBO;

    void setupMesh();
};

#endif // _MESH_H_