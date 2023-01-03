#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#include "ModelDraw.h"

GLfloat  colours[][4] = {
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
};

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

Mesh::Mesh() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
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

void Mesh::setupMesh() {
    glGenVertexArrays(1, &vaoIndex);

    // Point to VAO for this mesh
    glBindVertexArray(vaoIndex);

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

void Mesh::translate(GLfloat x, GLfloat y, GLfloat z) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}

void Mesh::scale(GLfloat x, GLfloat y, GLfloat z, bool saved) {
    modelMatrix = saved ? glm::scale(savedModelMatrix, glm::vec3(x, y, z)) : glm::scale(modelMatrix, glm::vec3(x, y, z));
}

void Mesh::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void Mesh::saveMatrix() {
    savedModelMatrix = modelMatrix;
}

void Drawer::loadTexture(std::string texturePath) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    GLint width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        textures.push_back(texture);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Drawer::Drawer() {
    // creating the view matrix
    view = glm::mat4(1.0f);

    // creating the projection matrix
    projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);
}
Mesh* Drawer::create() {
    size_t newIndex = assignedMeshes.size();
    Mesh newMesh = Mesh();
    assignedMeshes.push_back(newMesh);
    return &assignedMeshes[newIndex];
}

void Drawer::setup() {

    ShaderInfo  shaders[] =
    {
        { GL_VERTEX_SHADER, "media/triangles.vert" },
        { GL_FRAGMENT_SHADER, "media/triangles.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders(shaders);
    glUseProgram(program);

    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        assignedMeshes[i].setupMesh();
    }
    loadTexture("media/textures/lines.png");
    glUniform1i(glGetUniformLocation(program, "texture1"), textures[0]);
}

void Drawer::draw() {
    int viewLoc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        Mesh mesh = assignedMeshes[i];

        int mvpLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mesh.modelMatrix));

        mesh.draw();
    }
}

void Drawer::verticallyScaleMesh(size_t meshNumber, GLfloat value) {
    assignedMeshes[meshNumber].scale(1.0f, value, 1.0f, true);
}