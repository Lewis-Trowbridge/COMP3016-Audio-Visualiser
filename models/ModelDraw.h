#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "FileReader.h"
#include "../utils/utils.h"

class Mesh {
public:
    // mesh data
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normals;

    Mesh(unsigned int VAO, unsigned int VBO, unsigned int EBO);
    bool initFromFile(std::string filename);
    void setupMesh();
    void draw();
private:
    //  render data
    unsigned int VAO, VBO, EBO;
};

class Drawer {
public:
    Mesh* create();
    void draw();
private:
    std::vector<Mesh> assignedMeshes;
};



