#include "ModelDraw.h"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> indices, std::vector<Texture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
}

glm::vec3 stringToVec3(std::string valueString, std::string delimiter) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    return glm::vec3(stof(values[0]), stof(values[1]), stof(values[2]));
}

glm::vec2 stringToVec2(std::string valueString, std::string delimiter) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    return glm::vec2(stof(values[0]), stof(values[1]));
}

bool Mesh::initFromFile(std::string filename) {
    FileReader reader = FileReader();
    if (!reader.openFile(filename)) {
        return false;
    }
    std::string object = reader.getElement("object")[0];
    do {
        object = reader.getNextElement("object")[0];
        std::string stringValue;

        // Move the subposition to the first vertex
        vertices.push_back(stringToVec3(reader.getElementAttribute("object", "vertex"), " "));
        // Read the rest of the vertices
        while ((stringValue = reader.getNextElementAttribute("object", "vertex")) != "") {
            vertices.push_back(stringToVec3(stringValue, " "));
        }

        // Move the subposition to the first texcoord
        texCoords.push_back(stringToVec2(reader.getElementAttribute("object", "vertex-texture"), " "));
        // Read the rest of the texcoords
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-texture")) != "") {
            texCoords.push_back(stringToVec2(stringValue, " "));
        }

        // Move the subposition to the first normal
        normals.push_back(stringToVec3(reader.getElementAttribute("object", "vertex-normal"), " "));
        // Read the rest of the normal
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-normal")) != "") {
            normals.push_back(stringToVec3(stringValue, " "));
        }

        // Move the subposition to the first face
        std::vector<std::string> faceTriplets = splitString(reader.getElementAttribute("object", "face"), " ");
        for (int i = 0; i < faceTriplets.size(); i++)
        {
            indices.push_back(stringToVec3(faceTriplets[i], "/"));
        }
        // Read the rest of the faces
        while ((stringValue = reader.getNextElementAttribute("object", "face")) != "") {
            std::vector<std::string> faceTriplets = splitString(stringValue, " ");
            for (int i = 0; i < faceTriplets.size(); i++)
            {
                indices.push_back(stringToVec3(faceTriplets[i], "/"));
            }
        }
    } while (object != "");


    return true;
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
