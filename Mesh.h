#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Shader.h"

using namespace std;


class Mesh
{
public:
	Mesh(const float vertexPositions[], int size);
	virtual ~Mesh();
	void InitializeVertexBuffer();
	void LoadAssets();
	void Render(Shader shader);
	void UpdateSimulation(double simLength);

	GLfloat m_vertexPositions[1000];

	GLuint m_positionBufferObject;
	GLuint m_vao;
	//the offset we'll pass to the GLSL
	double m_offsetX = -0.5; //using different values from CPU and static GLSL examples, to make it clear this is working
	double m_offsetY = -0.5; //NOTE: we could use an array and pass the pointer, to be simpler & more efficent
	double m_offsetXSpeed = 0.2; //rate of change of offsetX in units per second
	double m_offsetYSpeed = 0.2; //rate of change of offsetY in units per second
};

