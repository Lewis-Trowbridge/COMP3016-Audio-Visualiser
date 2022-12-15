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

    Mesh();
    bool initFromFile(std::string filename);
    void Draw();
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};



