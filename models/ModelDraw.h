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
};

enum Attrib_IDs {
    vPosition = 0,
    tPosition = 1,
    nPosition = 2
};

class PhongLightingInfo {
public:
    glm::vec3 ambient;
    glm::vec3 lightPos;
    glm::vec3 diffuseColour;
    glm::vec3 specularColour;
    GLfloat shininess;

    PhongLightingInfo();
    void setup(GLint program);
};


class Mesh {
public:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normals;

    GLuint vaoIndex;
    Indexes bufferIndices;
    size_t numIndices;
    GLfloat colourScale;

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
    PhongLightingInfo lighting;
    std::vector<Mesh> assignedMeshes;
    std::vector<GLuint> textures;
    GLuint program;
};



