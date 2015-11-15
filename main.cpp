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

const float vertexPositions1[] = {
	0.0f, 0.5f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // Top
	-0.5f, -0.5f, 0.0f, 1.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,// Left
	0.5f, -0.5f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f// Right
};

int main( int argc, char* args[] )
{

	Display display(800, 600, "Hello World!");
	Mesh mesh(vertexPositions1, sizeof(vertexPositions1));
	Shader shader(path); //  Shader
	Texture texture(texturePath); // Create a texture
	Transform transform; // Transformations
	Camera camera(glm::vec3(0.f, 0.f, -3.f), 70.f, (float)800.f / (float)600.f, 0.1f, 100.0f);

	float value = 0.0f;
	

	while (!display.IsWindowClosed()) /// While the window is open
	{
		display.Clear(0.0f, 0.0f, 1.0f, 1.0f);
		float deltaTime = SDL_GetTicks() / 10000.f; // Not really Delta Time

		transform.GetPos().x = sinf(value);
		transform.GetRot().z = value;
		transform.SetScale(glm::vec3(cosf(value), cosf(value), cosf(value)));

		value += 0.01f;
		texture.Bind();
		mesh.Render(shader, transform, camera); // Draw the mesh
							 
		mesh.UpdateSimulation(deltaTime);
		display.Update(); // Update the display
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
