#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

class Texture
{
public:
	Texture(); // Default constructor
	Texture(const std::string& fileName);

	void Bind(); // Set OpenGL up to bind texture

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture; // Holds the handle to the texture
};

