#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <SDL.h>
#include <algorithm>

using namespace std;
class Shader
{
public:
	GLuint m_shader;
	GLuint m_program;
	GLuint m_positionLocation;
	GLuint m_offsetLocation;


	Shader(string shaderPath);
	virtual ~Shader();
	std::string LoadShader(const std::string& fileName); // Loads shader from file
	GLuint Shader::CreateShader(GLenum eShaderType, const std::string &strShaderFile); // Creates a shader
	GLuint CreateProgram(const std::vector<GLuint> &shaderList); // Creates shader program
};

