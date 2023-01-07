#ifndef _MODEL_H_
#define _MODEL_H_

#include "texture.h"
#include "mesh.h"

#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    Model(const char* path) {
        loadModel(path);
    }

    void draw(ShaderProgram& program);

private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // _MODEL_H_