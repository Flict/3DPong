#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <SDL.h>
#include <glm\glm.hpp>
#include "Shader.h"
#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

using namespace std;

std::string path = "./assets/shader"; // Path to shaders
std::string texturePath = "./assets/bricks.bmp"; // Path to brick texture
std::string texturePath2 = "./assets/crate.bmp"; // Path to crate texture

const float vertexPositions1[] = {
	// Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3

	// Back Face																  
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Back Top Left 4
	-0.5f, -0.5f, -0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Back Bottom Left 5
	0.5f, 0.5f, -0.5f, 1.0f,	0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Back Top Right 6
	0.5f, -0.5f, -0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Back Bottom Right	7
				
	// Left Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Front Top Left 8
	-0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Left 9
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Back Top Left 10
	-0.5f, -0.5f, -0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Back Bottom Left 11

	// Right Face
	0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Front Top Left 12
	0.5f, -0.5f, 0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Left 13
	0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Back Top Left 14
	0.5f, -0.5f, -0.5f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Back Bottom Left 15

	// Top Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Top Left 16
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Back Top Left 17
	0.5f, 0.5f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Top Right 18
	0.5f, 0.5f, -0.5f, 1.0f,	0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Right 19

	// Bottom Face
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Front Top Left 20
	-0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Back Top Left 21
	0.5f, -0.5f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Top Right 22
	0.5f, -0.5f, -0.5f, 1.0f,	0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Right 23
};

const unsigned int indicesPositions[] = {
	0, 1, 2, // Front Left triangle
	3, 2, 1, // Front Right triangle

	6, 5, 4, // Front Left triangle
	5, 6, 7, // Front Right triangle

	11, 9, 8,
	8, 10, 11,

	12, 13, 15,
	15, 14, 12, 

	19, 17, 16,
	16, 18, 19,

	20, 21, 23,
	23, 22, 20
};


void HandleInput(float deltaTime, Camera camera)
{
	SDL_Event event; // Used for storing the SDL event

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		
		{
			printf("entered switch detected\n");
		case SDL_KEYUP:
			camera.MoveForward(deltaTime);
			printf("Key press detected\n");
			break;
		}
	}
}

int main( int argc, char* args[] )
{

	Display display(800, 600, "Hello World!");
	//Mesh mesh(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));
	Mesh mesh2(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));
	Shader shader(path); //  Shader
	Texture texture(texturePath); // Create a texture
	Texture texture2(texturePath); // Create a texture
	Transform transform; // , Transformations
	Transform transform2; // , Transformations
	Camera camera(glm::vec3(0.f, 0.f, 3.f), 70.f, (float)800.f / (float)600.f, 0.1f, 100.0f);
	
	float value = 0.0f;
	
	while (!display.IsWindowClosed()) /// While the window is open
	{
		display.Clear(0.0f, 0.0f, 1.0f, 1.0f);
		float deltaTime = SDL_GetTicks() / 10000.f; // Not really Delta Time

		transform.GetRot().z = value;
		transform2.SetScale(glm::vec3(.1f, .3f, .1f));

		value += 0.01f;
		glBindTexture(GL_TEXTURE_2D, 0);
		//mesh.Render(shader, transform, camera); // Draw the mesh
		texture2.Bind();
		mesh2.Render(shader, transform2, camera); // Draw second mesh
							 
		//mesh.UpdateSimulation(deltaTime);
		mesh2.UpdateSimulation(deltaTime);

		//HandleInput(1, camera);
		display.Update(deltaTime, camera); // Update the display
	}


	//while (!done && (SDL_GetTicks() < 5000000)) //LOOP FROM HERE, for 2000ms (or if done flag is set)
	//	//WARNING: SDL_GetTicks is only accurate to milliseconds, use SDL_GetPerformanceCounter and SDL_GetPerformanceFrequency for higher accuracy
	//{
	//	//GET INPUT HERE - PLACEHOLDER

	//	mesh.UpdateSimulation(0.02); //call update simulation with an amount of time to simulate for (in seconds)
	//	  //WARNING - we are always updating by a constant amount of time. This should be tied to how long has elapsed
	//	    // see, for example, http://headerphile.blogspot.co.uk/2014/07/part-9-no-more-delays.html
 //       glViewport(0,0,800,600);
	//	display.Clear(0.0f, 0.0f, 1.0f, 1.0f);

	//	mesh.Render(*shader); //RENDER HERE - PLACEHOLDER

	//	//SDL_GL_SwapWindow(display->m_pWin);; //present the frame buffer to the display (swapBuffers)
	//	display.Update();

	//} //LOOP TO HERE

	//cleanup and exit
	//display->CleanUp();
	SDL_Quit();

	return 0;
}


