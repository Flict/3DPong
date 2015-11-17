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
std::string texturePath2 = "./assets/white-texture.bmp"; // Path to white texture
std::string texturePath3 = "./assets/background.bmp"; // Path to background texture
std::string texturePath4 = "./assets/sparks.bmp"; // Path to sparks texture

const float vertexPositions1[] = {
	// Front Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Front Top Left 0
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Bottom Left 1
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Right 2
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Right 3

	// Back Face																  
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Back Top Left 4
	-0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Back Bottom Left 5
	0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Back Top Right 6
	0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Bottom Right	7
				
	// Left Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Left 8
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Left 9
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Left 10
	-0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Back Bottom Left 11

	// Right Face
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Front Top Left 12
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Bottom Left 13
	0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Left 14
	0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Back Bottom Left 15

	// Top Face
	-0.5f, 0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Top Left 16
	-0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Back Top Left 17
	0.5f, 0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Top Right 18
	0.5f, 0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Right 19

	// Bottom Face
	-0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 1.0f, // Front Top Left 20
	-0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, // Back Top Left 21
	0.5f, -0.5f, 0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f, // Front Top Right 22
	0.5f, -0.5f, -0.5f, 1.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Back Top Right 23
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
			//camera.MoveForward(deltaTime);
			printf("Key press detected\n");
			break;
		}
	}
}

int main( int argc, char* args[] )
{

	Display display(800, 600, "Hello World!");
	Mesh paddle2(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));
	Mesh paddle1(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));
	Mesh ball(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));
	Mesh background(vertexPositions1, sizeof(vertexPositions1), indicesPositions, sizeof(indicesPositions));

	Shader shader(path); //  Shader
	Texture texture(texturePath); // Create a texture
	Texture texture2(texturePath2); // Create a texture
	Texture texture3(texturePath3); // Create a texture
	Texture texture4(texturePath4); // Create a texture
	Transform paddle1Transform; // , Transformations
	Transform paddle2Transform; // , Transformations
	Transform ballTransform;
	Transform backgroundTransform;
	Camera perspectiveCamera(glm::vec3(0.f, 0.f, 2.f), 70.f, (float)800.f / (float)600.f, 0.1f, 100.0f);
	Camera orthographicCamera(glm::vec3(0.f, 0.f, 3.f), -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 1000.0f);

	Camera renderCamera = orthographicCamera; // Camera used in the scene
	
	float value = 0.0f;

	backgroundTransform.GetPos().z = -3.0f;
	backgroundTransform.SetScale(glm::vec3(5.0f, 4.8f, 1.0f));

	paddle2Transform.GetPos().x = 0.9f;
	paddle1Transform.GetPos().x = -0.9f;
	ballTransform.GetPos().x = -0.8f;

	float ballSpeed = 15.f;
	glm::vec3 ballVelocity(ballSpeed, -ballSpeed, 0.0f); // Set the initial velocity

	paddle1Transform.SetScale(glm::vec3(.05f, .3f, .1f));
	paddle2Transform.SetScale(glm::vec3(.05f, .3f, .1f));
	ballTransform.SetScale(glm::vec3(.05f, .075f, .075f));

	double lastElapsedTime = SDL_GetTicks() - 1, deltaTime = 0.0f;
	while (!display.IsWindowClosed()) /// While the window is open
	{
		display.Clear(0.0f, 0.0f, 0.0f, 0.0f);
		// Calculate deltaTime from how long it took between frames
		double elapsedTime = SDL_GetTicks();
		deltaTime = (elapsedTime / lastElapsedTime) / 1000.0f;
		lastElapsedTime = elapsedTime;

		//cout << deltaTime << endl;
		if ((ballTransform.GetPos().x) > 1) // Point for player1
		{
			ballTransform.GetPos().x = 0.8f;
			ballTransform.GetPos().y = paddle2Transform.GetPos().y;
			ballVelocity.x = -ballVelocity.x;
			cout << "Player 1 Point" << endl;
		}
		else if (ballTransform.GetPos().x < -1) // Point for player2
		{
			ballTransform.GetPos().x = -0.8f;
			ballTransform.GetPos().y = paddle1Transform.GetPos().y;
			ballVelocity.x = -ballVelocity.x;
			cout << "Player 2 Point" << endl;
		}

		background.Render(shader, paddle1Transform, renderCamera);
		
		ballTransform.GetPos() += (ballVelocity * (float)deltaTime);

		if (ballTransform.GetPos().y > 0.9 || ballTransform.GetPos().y < -0.9)
				ballVelocity.y = -ballVelocity.y;
			

		if (display.m_perspective) // perspective projection
		{
			display.Clear(0.0f, 0.0f, 0.0f, 0.0f);
			renderCamera = perspectiveCamera;
			texture3.Bind();
			background.Render(shader, backgroundTransform, renderCamera);
			glBindTexture(GL_TEXTURE_2D, 0); // No texture
			texture.Bind();
			paddle1.Render(shader, paddle1Transform, renderCamera); // Draw the mesh
			paddle2.Render(shader, paddle2Transform, renderCamera); // Draw second mesh
			glBindTexture(GL_TEXTURE_2D, 0); // No texture
			texture4.Bind();
			ball.Render(shader, ballTransform, renderCamera);
			glBindTexture(GL_TEXTURE_2D, 0); // No texture
		}
		else // orthographic projection
		{
			display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
			renderCamera = orthographicCamera;
			glBindTexture(GL_TEXTURE_2D, 0); // No texture
			paddle1.Render(shader, paddle1Transform, renderCamera); // Draw the mesh
			paddle2.Render(shader, paddle2Transform, renderCamera); // Draw second mesh
			ball.Render(shader, ballTransform, renderCamera);
			//texture2.Bind();
		}

		
		if (ballTransform.GetPos().y <= paddle2Transform.GetPos().y + 0.1 && ballTransform.GetPos().y > paddle2Transform.GetPos().y - 0.1 && ballTransform.GetPos().x >= paddle2Transform.GetPos().x - 0.05)
			ballVelocity = -ballVelocity;
		else if (ballTransform.GetPos().y <= paddle1Transform.GetPos().y + 0.1 && ballTransform.GetPos().y > paddle1Transform.GetPos().y - 0.1 && ballTransform.GetPos().x <= paddle1Transform.GetPos().x + 0.05 && ballTransform.GetPos().x >paddle1Transform.GetPos().x - 0.05)
			ballVelocity = -ballVelocity;
			//paddle1Transform.GetRot().z = value;

		value += 0.01f;
		
		display.Update(deltaTime, renderCamera, paddle1Transform, paddle2Transform, paddle1Transform); // Update the display
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


