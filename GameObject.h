#pragma once

#include "Mesh.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

private:
	Mesh mesh; // Objects Mesh
};

