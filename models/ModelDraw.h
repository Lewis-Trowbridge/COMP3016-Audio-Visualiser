#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#include <vector>
#include <string>
#include <GL/glew.h>
#include "../LoadShaders.h"
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

enum Attrib_IDs {
    vPosition = 0, cPosition = 1, tPosition = 2 
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

    glm::mat4 modelMatrix;

    Mesh();
    bool initFromFile(std::string filename);
    void setupMesh();
    void draw();
    void translate(GLfloat x, GLfloat y, GLfloat z);
    void scale(GLfloat x, GLfloat y, GLfloat z, bool saved);
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void saveMatrix();
private:
    glm::mat4 savedModelMatrix;
};

class Drawer {
public:
    Drawer();
    Mesh* create();
    void setup();
    void draw();
    void loadTexture(std::string texturePath);
    void verticallyScaleMesh(size_t meshNumber, GLfloat value);

    glm::mat4 view;
    glm::mat4 projection;
private:
    std::vector<Mesh> assignedMeshes;
    std::vector<GLuint> textures;
    GLuint program;
};



