#include "Mesh.h"

Mesh::Mesh(const float vertexPositions[], int size)
{
	for (int i = 0; i < size; i++)
	{
		m_vertexPositions[i] = vertexPositions[i];
	}

	LoadAssets();
}


Mesh::~Mesh()
{
}

void Mesh::InitializeVertexBuffer()
{
	glGenBuffers(1, &m_positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexPositions), m_vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	cout << "positionBufferObject created OK! GLUint is: " << m_positionBufferObject << endl;
}

void Mesh::LoadAssets()
{
	//initializeProgram(); //create GLSL Shaders, link into a GLSL program

	InitializeVertexBuffer(); //load data into a vertex buffer

	glGenVertexArrays(1, &m_vao); //create a Vertex Array Object
	glBindVertexArray(m_vao); //make the VAO active
	cout << "Vertex Array Object created OK! GLUint is: " << m_vao << std::endl;

	cout << "Loaded Assets OK!\n";
}

void Mesh::Render(Shader shader)
{
	glUseProgram(shader.m_program); //installs the program object specified by program as part of current rendering state

									 //load data to GLSL that **may** have changed
	//glUniform2f(shader.m_offsetLocation, m_offsetX, m_offsetY);


	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject); //bind positionBufferObject

	glEnableVertexAttribArray(shader.m_positionLocation); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
														   //more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	glVertexAttribPointer(shader.m_positionLocation, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0

	glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	glDisableVertexAttribArray(0); //cleanup
	glUseProgram(0); //clean up

}

void Mesh::UpdateSimulation(double simLength) //update simulation with an amount of time to simulate for (in seconds)
{
	m_offsetX += m_offsetXSpeed * simLength;
	m_offsetY += m_offsetYSpeed * simLength;
}
