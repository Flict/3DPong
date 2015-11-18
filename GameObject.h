#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject(const GLfloat vertices[], GLint verticesSize, const GLuint indices[], GLint indicesSize, 
				glm::vec3 position = glm::vec3(0.f, 0.f, 0.f)); // Constructor
	virtual ~GameObject();

	Transform transform; // Objects Transformations
	Mesh m_mesh; // Objects Mesh

private:
	
	Texture texture; // Objects texture
public:
	GLvoid Update(GLfloat deltaTime);
	GLvoid Draw(Camera& camera);
};

