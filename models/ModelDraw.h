#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "FileReader.h"
#include "../utils/utils.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:
    // mesh data
    std::vector<glm::vec3>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh();
    bool initFromFile(std::string filename);
    void Draw();
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};



