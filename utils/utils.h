#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr

std::vector<std::string> splitString(std::string toSplit, std::string delimiter);

void setUniform(GLint program, std::string name, float* value);
void setUniform(GLint program, std::string name, glm::mat4* value);
void setUniform(GLint program, std::string name, glm::vec3* value);
void setUniform(GLint program, std::string name, glm::vec4* value);