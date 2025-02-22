#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#include "ModelDraw.h"

void insertStringValuesToGLVector(std::string valueString, std::string delimiter, std::vector<GLfloat>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i++) {
        recipient->push_back(stof(values[i]));
    }
}

void insertStringValuesToGLVector(std::string valueString, std::string delimiter, std::vector<GLuint>* recipient) {
    std::vector<std::string> values = splitString(valueString, delimiter);
    for (int i = 0; i < values.size(); i++) {
        recipient->push_back(stoul(values[i]) -1);
    }
}

PhongLightingInfo::PhongLightingInfo() {
    ambient = glm::vec3(0.9f, 0.9f, 0.9f);
    lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
    diffuseColour = glm::vec3(0.9f, 0.9f, 0.9f);
    specularColour = glm::vec3(0.0f, 0.0f, 1.0f);
    shininess = 128;
}

void PhongLightingInfo::setup(GLint program) {
    setUniform(program, "ambient", &ambient);

    setUniform(program, "lightPos", &lightPos);

    setUniform(program, "diffuseColour", &diffuseColour);

    setUniform(program, "specularColour", &specularColour);

    setUniform(program, "shininess", &shininess);
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

    std::vector<GLfloat> vertexData = std::vector<GLfloat>();
    std::vector<GLfloat> texCoordsData = std::vector<GLfloat>();
    std::vector<GLfloat> normalsData = std::vector<GLfloat>();
    std::vector<GLuint> facesData = std::vector<GLuint>();

    std::string object = reader.getElement("object")[0];
    do {
        object = reader.getNextElement("object")[0];
        std::string stringValue;

        // Move the subposition to the first vertex
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex"), " ", &vertexData);
        // Read the rest of the vertices
        while ((stringValue = reader.getNextElementAttribute("object", "vertex")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &vertexData);
        }

        // Move the subposition to the first texcoord
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex-texture"), " ", &texCoordsData);
        // Read the rest of the texcoords
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-texture")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &texCoordsData);
        }

        // Move the subposition to the first normal
        insertStringValuesToGLVector(reader.getElementAttribute("object", "vertex-normal"), " ", &normalsData);
        // Read the rest of the normal
        while ((stringValue = reader.getNextElementAttribute("object", "vertex-normal")) != "") {
            insertStringValuesToGLVector(stringValue, " ", &normalsData);
        }

        // Move the subposition to the first face
        std::vector<std::string> faceTriplets = splitString(reader.getElementAttribute("object", "face"), " ");
        for (int i = 0; i < faceTriplets.size(); i++)
        {
            insertStringValuesToGLVector(faceTriplets[i], "/", &facesData);
        }
        // Read the rest of the faces
        while ((stringValue = reader.getNextElementAttribute("object", "face")) != "") {
            std::vector<std::string> faceTriplets = splitString(stringValue, " ");
            for (int i = 0; i < faceTriplets.size(); i++)
            {
                insertStringValuesToGLVector(faceTriplets[i], "/", &facesData);
            }
        }
    } while (object != "");

    // Reorganising of data according to face data
    for (int i = 0; i < facesData.size(); i+=9) {
        for (int j = 0; j < 9; j+=3) {
            // Grab vertices at positions specified in OBJ file
            vertices.push_back(vertexData[3 * facesData[i + j]]);
            vertices.push_back(vertexData[3 * facesData[i + j] + 1]);
            vertices.push_back(vertexData[3 * facesData[i + j] + 2]);
            // Grab tex coords at positions specified in OBJ file
            texCoords.push_back(texCoordsData[2 * facesData[i + j + 1]]);
            texCoords.push_back(texCoordsData[2 * facesData[i + j + 1] + 1]);
            // Grab normals at positions specified in OBJ file
            normals.push_back(normalsData[3 * facesData[i + j + 2]]);
            normals.push_back(normalsData[3 * facesData[i + j + 2] + 1]);
            normals.push_back(normalsData[3 * facesData[i + j + 2] + 2]);
        }
    }

    for (GLint i = 0; i < facesData.size() / 3; i++) {
        indices.push_back(i);
    }


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

    // Prepare tex coords data
    glGenBuffers(1, &bufferIndices.texCoords);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices.texCoords);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat),
        texCoords.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(tPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Prepare normals data
    glGenBuffers(1, &bufferIndices.normals);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIndices.normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat),
        normals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(nPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    numIndices = indices.size();

    // Enable all VBOs
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(tPosition);
    glEnableVertexAttribArray(nPosition);
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
    lighting.setup(program);
}

void Drawer::draw() {
    setUniform(program, "view", &view);
    setUniform(program, "projection", &projection);

    for (size_t i = 0; i < assignedMeshes.size(); i++)
    {
        Mesh mesh = assignedMeshes[i];

        setUniform(program, "model", &mesh.modelMatrix);
        setUniform(program, "scale", &mesh.colourScale);

        mesh.draw();
    }
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

void Drawer::verticallyScaleMesh(size_t meshNumber, GLfloat value) {
    assignedMeshes[meshNumber].scale(1.0f, value, 1.0f, true);
    assignedMeshes[meshNumber].colourScale = value;
}