#include "utils.h"

std::vector<std::string> splitString(std::string toSplit, std::string delimiter) {
	std::vector<std::string> result = std::vector<std::string>();
	size_t end = toSplit.find(delimiter);
	while (end != std::string::npos) {
		result.push_back(toSplit.substr(0, end));
		toSplit = toSplit.substr(++end);
		end = toSplit.find(delimiter);
	}
	result.push_back(toSplit);
	return result;
}

void setUniform(GLint program, std::string name, float* value) {
	GLuint loc = glGetUniformLocation(program, name.c_str());
	glUniform1fv(loc, 1, value);
}

void setUniform(GLint program, std::string name, glm::mat4* value) {
	GLuint loc = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(*value));
}

void setUniform(GLint program, std::string name, glm::vec3* value) {
	GLuint loc = glGetUniformLocation(program, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(*value));
};
void setUniform(GLint program, std::string name, glm::vec4* value) {
	GLuint loc = glGetUniformLocation(program, name.c_str());
	glUniform4fv(loc, 1, glm::value_ptr(*value));
};