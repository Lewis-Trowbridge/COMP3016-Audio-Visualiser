#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "FileReader.h"
#include "../utils/utils.h"


struct Indexes {
public:
    GLuint vertices;
    GLuint indices;
    GLuint texCoords;
    GLuint normals;
    GLuint colours;
};

class Mesh {
public:
    // mesh data
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normals;
    //std::vector<GLfloat> colours;
    GLuint vaoIndex;
    Indexes bufferIndices;
    size_t numIndices;

    glm::mat4 model;

    bool initFromFile(std::string filename);
    void setupMesh();
    void draw();
};

class Drawer {
public:
    Mesh* create();
    void setup();
    void draw();

    glm::mat4 view;
    glm::mat4 projection;
private:
    std::vector<Mesh> assignedMeshes;
};



