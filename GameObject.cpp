#include "GameObject.h"

GameObject::GameObject(const GLfloat vertices[], GLint verticesSize, const GLuint indices[], GLint indicesSize, glm::vec3 position)
{
	m_mesh = Mesh(vertices, sizeof(vertices), indices, sizeof(indices)); // Create a new mesh for the game object
	transform = Transform(position); // Set the position of the mesh
}


GameObject::~GameObject()
{
}


GLvoid GameObject::Update(GLfloat deltaTime)
{
}


GLvoid GameObject::Draw(Camera& camera)
{
	m_mesh.Draw(transform, camera);
}
