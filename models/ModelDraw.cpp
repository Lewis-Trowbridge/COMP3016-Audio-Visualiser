#include "ModelDraw.h"

GLfloat  colours[][4] = {
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
};

enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

void insertStringValuesToGLVector(std::string valueString, std::string delimiter, std::vector<GLfloat>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i++) {
        recipient->push_back(stof(values[i]));
    }
}

void insertStringValuesToGLVector(std::string valueString, std::string delimiter, std::vector<GLuint>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i+=3) {
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
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex"), " ", &vertices);
        // Read the rest of the vertices
        while ((stringValue = reader.getNextElementAttribute("object", "vertex")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &vertices);
        }

        // Move the subposition to the first texcoord
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex-texture"), " ", &texCoords);
        // Read the rest of the texcoords
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-texture")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &texCoords);
        }

        // Move the subposition to the first normal
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex-normal"), " ", &normals);
        // Read the rest of the normal
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-normal")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &normals);
        }

        // Move the subposition to the first face
        std::vector<std::string> faceTriplets = splitString(reader.getElementAttribute("object", "face"), " ");
        for (int i = 0; i < faceTriplets.size(); i++)
        {
            insertStringValuesToGLVector(faceTriplets[i], "/", &indices);
        }
        // Read the rest of the faces
        while ((stringValue = reader.getNextElementAttribute("object", "face")) != "") {
            std::vector<std::string> faceTriplets = splitString(stringValue, " ");
            for (int i = 0; i < faceTriplets.size(); i++)
            {
                insertStringValuesToGLVector(faceTriplets[i], "/", &indices);
            }
        }
    } while (object != "");


    return true;
}

void Mesh::setupMesh(GLuint vaoIndex) {
    this->vaoIndex = vaoIndex;

    // Point to VAO for this mesh
    glBindVertexArray(this->vaoIndex);

    // Prepare vertex data
    glGenBuffers(1, &bufferIndices.vertices);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices.vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
        vertices.data(), GL_STATIC_DRAW);

    // Prepare indices data
    glGenBuffers(1, &bufferIndices.indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndices.indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Prepare colours data
    glGenBuffers(1, &bufferIndices.colours);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices.colours);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(colours), colours, 0);

    glVertexAttribPointer(cPosition, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Prepare tex coords data
    glGenBuffers(1, &bufferIndices.texCoords);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices.texCoords);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat),
        texCoords.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(tPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    numIndices = indices.size();

    // Enable all VBOs
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(cPosition);
    glEnableVertexAttribArray(tPosition);
}

void Mesh::draw() {
    glBindVertexArray(vaoIndex);
    glBindTexture(GL_TEXTURE_2D, 1);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

Mesh* Drawer::create() {
    size_t newIndex = assignedMeshes.size();
    Mesh newMesh = Mesh();
    assignedMeshes.push_back(newMesh);
    return &assignedMeshes[newIndex];
}

void Drawer::setup() {
    VAOs.resize(assignedMeshes.size());
    glGenVertexArrays(assignedMeshes.size(), VAOs.data());
    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        assignedMeshes[i].setupMesh(VAOs[i]);
    }
}

void Drawer::draw() {
    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        assignedMeshes[i].draw();
    }
}