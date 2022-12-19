#include "ModelDraw.h"

GLfloat  colours[][4] = {
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
};

Mesh::Mesh(unsigned int VAO, unsigned int VBO, unsigned int EBO) {
    this->VAO = VAO;
    this->VBO = VBO;
    this->EBO = EBO;
    this->vertices = std::vector<GLfloat>();
    this->indices = std::vector<GLuint>();
    this->texCoords = std::vector<GLfloat>();
    this->normals = std::vector<GLfloat>();
}

void insertStringFloatsToGLfloatVector(std::string valueString, std::string delimiter, std::vector<GLfloat>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i++) {
        recipient->push_back(stof(values[i]));
    }
}

void insertStringFloatsToGLfloatVector(std::string valueString, std::string delimiter, std::vector<GLuint>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i++) {
        recipient->push_back(stoul(values[i]) -1);
    }
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
        insertStringFloatsToGLfloatVector(reader.getElementAttribute("object", "vertex"), " ", &vertices);
        // Read the rest of the vertices
        while ((stringValue = reader.getNextElementAttribute("object", "vertex")) != "") {
            insertStringFloatsToGLfloatVector(stringValue, " ", &vertices);
        }

        // Move the subposition to the first texcoord
        insertStringFloatsToGLfloatVector(reader.getElementAttribute("object", "vertex-texture"), " ", &texCoords);
        // Read the rest of the texcoords
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-texture")) != "") {
            insertStringFloatsToGLfloatVector(stringValue, " ", &texCoords);
        }

        // Move the subposition to the first normal
        insertStringFloatsToGLfloatVector(reader.getElementAttribute("object", "vertex-normal"), " ", &normals);
        // Read the rest of the normal
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-normal")) != "") {
            insertStringFloatsToGLfloatVector(stringValue, " ", &normals);
        }

        // Move the subposition to the first face
        std::vector<std::string> faceTriplets = splitString(reader.getElementAttribute("object", "face"), " ");
        for (int i = 0; i < faceTriplets.size(); i++)
        {
            insertStringFloatsToGLfloatVector(faceTriplets[i], "/", &indices);
        }
        // Read the rest of the faces
        while ((stringValue = reader.getNextElementAttribute("object", "face")) != "") {
            std::vector<std::string> faceTriplets = splitString(stringValue, " ");
            for (int i = 0; i < faceTriplets.size(); i++)
            {
                insertStringFloatsToGLfloatVector(faceTriplets[i], "/", &indices);
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

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        &indices[0], GL_STATIC_DRAW);

    //// vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(VAO, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //// vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //// vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}

Mesh* Drawer::create() {
    // Work out what the new OpenGL indexes should be
    size_t newIndex = assignedMeshes.size();
    size_t openGLIndex = newIndex * 4;
    Mesh newMesh = Mesh(openGLIndex + 1, openGLIndex + 2, openGLIndex + 3);
    newMesh.pointerIndices.vertices = openGLIndex;
    newMesh.pointerIndices.indices = openGLIndex + 1;
    newMesh.pointerIndices.texCoords = openGLIndex + 2;
    newMesh.pointerIndices.normals = openGLIndex + 3;
    assignedMeshes.push_back(newMesh);
    return &assignedMeshes[newIndex];
}

void Drawer::setup() {
    VAOs.resize(assignedMeshes.size());
    glGenVertexArrays(assignedMeshes.size(), VAOs.data());
    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        Mesh meshToDraw = assignedMeshes[i];

        // Point to VAO for this mesh
        glBindVertexArray(VAOs[i]);

        // Prepare vertex data
        glGenBuffers(1, &meshToDraw.bufferIndices.vertices);
        glBindBuffer(GL_ARRAY_BUFFER, meshToDraw.bufferIndices.vertices);
        glBufferData(GL_ARRAY_BUFFER, meshToDraw.vertices.size() * sizeof(GLfloat),
            meshToDraw.vertices.data(), GL_STATIC_DRAW);

        // Prepare indices data
        glGenBuffers(1, &meshToDraw.bufferIndices.indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshToDraw.bufferIndices.indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshToDraw.indices.size() * sizeof(GLuint),
            meshToDraw.indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Prepare tex coords data
        //glGenBuffers(1, &meshToDraw.bufferIndices.texCoords);
        //glBindBuffer(GL_ARRAY_BUFFER, meshToDraw.bufferIndices.texCoords);
        //glBufferData(GL_ARRAY_BUFFER, meshToDraw.texCoords.size() * sizeof(GLfloat),
        //    meshToDraw.texCoords.data(), GL_STATIC_DRAW);

        //glVertexAttribPointer(meshToDraw.pointerIndices.texCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(meshToDraw.pointerIndices.texCoords);
        //glBindVertexArray(0);
    }
}

void Drawer::draw() {
    for (size_t i = 0; i < VAOs.size(); i++)
    {
        size_t numVertices = assignedMeshes[i].indices.size() / 3;
        glBindVertexArray(VAOs[i]);
        //glBindTexture(GL_TEXTURE_2D, 1);
        glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
    }
}