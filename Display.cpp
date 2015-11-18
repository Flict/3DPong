#include "Display.h"

Display::Display(GLint width, GLint height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING); // Initialise SDL

								   // Set RGB colour data to 32 bit
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Number of bits for displaying the colour red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Number of bits for displaying the colour green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Number of bits for displaying the colour blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Number of bits for displaying the colour alpha

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // How many bits to allocate for a single pixel 32 / 4(each colour)
												 //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Allocate space for two windows, which can be used for layering objects and for drawing to one buffer window while another displays.

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); // Creates an SDL Window and stores the pointer
	m_glContext = SDL_GL_CreateContext(m_window); // Create the OpenGL context

	GLenum status = glewInit(); // Initialise GLEW
	if (status != GLEW_OK) // Error
	{
		std::cerr << "Glew failed to initialize!" << std::endl; // Output a console error
	}

	m_isWindowClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	for (int i = 0; i < 322; i++)
	{
		KEYS[i] = false; // Initialise all keys to false
	}
	//SDL_EnableKeyRepeat()
	//SDL_SetRelativeMouseMode(SDL_TRUE);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext); // Deletes the OpenGL context
	SDL_DestroyWindow(m_window); // Destroy the Window
	SDL_Quit(); // De-initialise Window
}

void Display::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a); // Fill the display with colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the colour buffer so we can fill it with the display colour
}
float rot = 0.1f, pitch = 0.1f;
void Display::Update(float deltaTime, Camera& camera, Transform& paddle1, Transform& paddle2, Transform& ball)
{
	SDL_GL_SwapWindow(m_window); // Swap the window buffers

	SDL_Event e; // Create an SDL event structure for handling OS events

	while (SDL_PollEvent(&e)) // 
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_isWindowClosed = true; // Set that the window is closed
			break;
		case SDL_KEYDOWN:
			//KEYS[e.key.keysym.sym] = true; // Set key is down
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				if (!m_cameraMode)
				{
					if (((paddle1.GetPos().y + 0.2f) + deltaTime * 30.f) <= 1)
						paddle1.GetPos().y += deltaTime * 30.f;
				}
					
				else
					camera.MoveForward(deltaTime * 30.0f);
				break;
			case SDLK_s:
				if (!m_cameraMode)
				{
					if (((paddle1.GetPos().y - 0.2f) - deltaTime * 30.f) >= -1)
						paddle1.GetPos().y -= deltaTime * 30.f;
				}
				else
					camera.MoveForward(deltaTime * -30.0f);
				break;
			case SDLK_a:
				if (m_cameraMode)
				camera.MoveRight(deltaTime * 30.f);
				break;
			case SDLK_d:
				if (m_cameraMode)
					camera.MoveRight(deltaTime * -30.f);
				break;
			case SDLK_UP:
				if (!m_cameraMode)
				{
					if (((paddle2.GetPos().y + 0.2f) + deltaTime * 30.f) <= 1)
						paddle2.GetPos().y += deltaTime * 30.f;
				}
				else
				camera.Pitch(pitch);
				break;
			case SDLK_DOWN:
				if (!m_cameraMode)
				{
					if (((paddle2.GetPos().y - 0.2f) - deltaTime * 30.f) >= -1)
						paddle2.GetPos().y -= deltaTime * 30.f;
				}	
				else
					camera.Pitch(-pitch);
				break;
			case SDLK_LEFT:
				if (m_cameraMode)
				camera.RotateY(pitch);
				break;
			case SDLK_RIGHT:
				if (m_cameraMode)
				camera.RotateY(-pitch);
				break;
			case SDLK_F1:
				m_perspective = !m_perspective; // Switch between mode value
				break;
			case SDLK_F2:
				m_cameraMode = !m_cameraMode; // Switch between mode value
				break;
			case SDLK_F3: // View port standard
				m_viewPort = STANDARD;
				break;
			case SDLK_F4: // View port follow ball
				m_viewPort = FOLLOWBALL;
				break;
			case SDLK_F5: // View port follow ball
				m_viewPort = PADDLE1;
				break;
			case SDLK_F6: // View port follow ball
				m_viewPort = PADDLE2;
				break;
			}
			break;
			
		case SDL_KEYUP:
			//KEYS[e.key.keysym.sym] = false; // Set key is up
			break;
		}


	}
}

bool Display::IsWindowClosed()
{
	return m_isWindowClosed;
}

//Display::Display(GLint width, GLint height, const std::string& title)
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//		cout << "SDL_Init Error: " << SDL_GetError() << endl;
//		exit(1);
//	}
//	cout << "SDL initialised OK!\n";
//
//	CreateWindow(width, height, title);
//}
//
//
//Display::~Display()
//{
//}
//
//void Display::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
//{
//	glClearColor(r, g, b, a); // Fill the display with colour
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the colour buffer so we can fill it with the display colour
//}
//
//void Display::CreateWindow(GLint width, GLint height, const std::string& title)
//{
//	//create window
//	m_pWin = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); //same height and width makes the window square ...
//
//	//error handling
//	if (m_pWin == nullptr)
//	{
//		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		exit(1);
//	}
//	cout << "SDL CreatedWindow OK!\n";
//}
//
//void Display::CreateContext()
//{
//	m_context = SDL_GL_CreateContext(m_pWin);
//	if (m_context == nullptr) {
//		SDL_DestroyWindow(m_pWin);
//		std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		exit(1);
//	}
//	cout << "Created OpenGL context OK!\n";
//}
//
//void Display::CleanUp()
//{
//	SDL_GL_DeleteContext(m_context);
//	SDL_DestroyWindow(m_pWin);
//	cout << "Cleaning up OK!\n";
//}
//
//void Display::SetGLAttributes()
//{
//	cout << "Built for OpenGL Version 3.3" << endl; //ahttps://en.wikipedia.org/wiki/OpenGL_Shading_Language#Versions
//													// set the opengl context version
//	int major = 3;
//	int minor = 3;
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //core profile
//	cout << "Set OpenGL context to version " << major << "." << minor << " OK!\n";
//}
//
//void Display::InitGlew()
//{
//	GLenum rev;
//	glewExperimental = GL_TRUE; //GLEW isn't perfect - see https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
//	rev = glewInit();
//	if (GLEW_OK != rev) {
//		std::cout << "GLEW Error: " << glewGetErrorString(rev) << std::endl;
//		SDL_Quit();
//		exit(1);
//	}
//	else {
//		cout << "GLEW Init OK!\n";
//	}
//}
