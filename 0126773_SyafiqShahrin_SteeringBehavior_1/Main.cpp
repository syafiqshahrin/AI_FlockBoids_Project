#include <glad/glad.h>
#include <glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iterator>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "MeshObject.h"
#include "Entity.h"
#include "UIHandler.h"
#include "Button.h"
#include "SteeringScene.h"



InputData inputData;
float DeltaTime = 0.0f;
int windowWidth = 1600;
int windowHeight = 1000;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		inputData.mouseInWindow = true;
	}
	else
	{
		inputData.mouseInWindow = false;
		// The cursor left the content area of the window
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	glfwGetCursorPos(window, &xpos, &ypos);
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	Vector2 mouseCoord((xpos/ (float)windowWidth) *(2.0f *  (aspectRatio * 10)) - (aspectRatio * 10), -((ypos/ (float)windowHeight) * (2.0f * 10.0f) - (1.0f * 10)));
	
	inputData.mousePosition = mouseCoord;
	//std::cout << "x: " << mouseCoord.x << ", y: " << mouseCoord.y << std:: endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		inputData.isRightClicked = true;
		//std::cout << "Clicked Right Button" << std::endl;
	}
	else
	{
		inputData.isRightClicked = false;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		inputData.isLeftClicked = true;
		//std::cout << "Clicked Left Button" << std::endl;
	}
	else
	{
		inputData.isLeftClicked = false;
		
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		inputData.uiKeyToggle = !inputData.uiKeyToggle;
		//std::cout << "Pressed E Button" << std::endl;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		inputData.clearObjects = true;
		//std::cout << "Pressed E Button" << std::endl;
	}
	else
	{
		inputData.clearObjects = false;
	}


	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		inputData.UpButtonPressed = true;
	}
	else if(key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		inputData.UpButtonPressed = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		inputData.DownButtonPressed = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		inputData.DownButtonPressed = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		inputData.LeftButtonPressed = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		inputData.LeftButtonPressed = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		inputData.RightButtonPressed = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		inputData.RightButtonPressed = false;
	}

}




int main()
{
	srand(static_cast <unsigned> (time(0)));
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	const char* windowTitle = "0126773_SyafiqShahrin_AI_Boids";

	//creates glfw window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//set the callback for window resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetWindowSizeLimits(window, 1600, 1000, 1600, 1000);
	//Initializing GLAD 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad" << std::endl;
		return -1;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	glfwSwapInterval(0);
	//
	
	SteeringScene steeringScene(&windowWidth, &windowHeight,&DeltaTime);
	while (!glfwWindowShouldClose(window))
	{
		float frameStartTime = glfwGetTime();

		
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		//glClearColor(68.0f/255.0f, 74.0f / 255.0f, 70.0f / 255.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//=======Draw=======//
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		steeringScene.UpdateInput(inputData);
		steeringScene.UpdateScene();
		steeringScene.DrawScene();
	
		//=======Draw End=======//
		glfwSwapBuffers(window);
		glfwPollEvents();
		float frameEndTime = glfwGetTime();
		DeltaTime = frameEndTime - frameStartTime;
		//std::cout << "delta time: " << DeltaTime * 1000.0 << "ms" << std::endl;
	

	}


	glfwTerminate();
	return 0;
}

