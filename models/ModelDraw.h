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

// A class to contain all lighting information to implement the Phong lighting model.
class PhongLightingInfo {
public:
    glm::vec3 ambient;
    glm::vec3 lightPos;
    glm::vec3 diffuseColour;
    glm::vec3 specularColour;
    GLfloat shininess;

    PhongLightingInfo();
    // Sets up lighting uniforms in OpenGL.
    void setup(GLint program);
};

// A class that represents a single mesh.
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
    // Initialises a mesh's data from a file.
    bool initFromFile(std::string filename);
    // Loads mesh data into OpenGL. Do not call yourself, call Drawer.setup instead.
    void setupMesh();
    // Draws data in OpenGL. DO not call yourself, call Drawer.draw instead.
    void draw();
    // Performs a translation on the mesh's model matrix.
    void translate(GLfloat x, GLfloat y, GLfloat z);
    // Performs a scale on the mesh's model matrix. Use saved=true to perform on the saved matrix rather than the current model matrix.
    void scale(GLfloat x, GLfloat y, GLfloat z, bool saved);
    // Performs a rotation on the mesh's model matrix.
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    // Save the current model matrix to be used as a base for future operations.
    void saveMatrix();
private:
    glm::mat4 savedModelMatrix;
};

// A class that handles the setup and drawing of all assigned meshes.
class Drawer {
public:
    Drawer();
    // Creates and registers a mesh, returning a pointer to the mesh for initialisation.
    Mesh* create();
    // Sets up all registered meshes.
    void setup();
    // Draws all registered meshes.
    void draw();
    // Loads and registers a texture
    void loadTexture(std::string texturePath);
    // Vertically scales a given mesh by a given value.
    void verticallyScaleMesh(size_t meshNumber, GLfloat value);

    glm::mat4 view;
    glm::mat4 projection;
private:
    PhongLightingInfo lighting;
    std::vector<Mesh> assignedMeshes;
    std::vector<GLuint> textures;
    GLuint program;
};



