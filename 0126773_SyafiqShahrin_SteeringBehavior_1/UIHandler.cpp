#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"
#include "UIHandler.h"



void UIHandler::Play()
{
	isPlaying = !isPlaying;
	std::cout << "Play Button Clicked" << std::endl;
}

void UIHandler::Clear()
{
	clearMap = true;
	std::cout << "Clear Button Clicked" << std::endl;
}

void UIHandler::IncreaseCellMapDimensions()
{
	clearMap = true;
	cellMapDimension += 10.0f;
	
	if (cellMapDimension > 20.0f && cellMapDimension < 50.0f)
	{
		cellMapDimension = 50.0f;
	}
	else if (cellMapDimension > 50.0f && cellMapDimension < 100.0f)
	{
		cellMapDimension = 100.0f;
	}
	else if (cellMapDimension > 100.0f && cellMapDimension < 250.0f)
	{
		cellMapDimension = 250.0f;
	}
	else if (cellMapDimension > 250.0f && cellMapDimension < 500.0f)
	{
		cellMapDimension = 500.0f;
	}
	else if (cellMapDimension > 500.0f && cellMapDimension < 1000.0f)
	{
		cellMapDimension = 1000.0f;
	}
	else if (cellMapDimension > 1000.0f)
	{
		cellMapDimension = 1000.0f;
	}
	std::cout << "Increase Button Clicked" << std::endl;
	
	std::cout << "Increase Button Clicked: Grid dimensions - " << cellMapDimension << " x " << cellMapDimension << std::endl;
}

void UIHandler::DecreaseCellMapDimensions()
{
	clearMap = true;
	cellMapDimension -= 10.0f;
	
	if (cellMapDimension > 500.0f && cellMapDimension < 1000.0f)
	{
		cellMapDimension = 500.0f;
	}
	else if (cellMapDimension > 250.0f && cellMapDimension < 500.0f)
	{
		cellMapDimension = 250.0f;
	}
	else if (cellMapDimension > 100.0f && cellMapDimension < 250.0f)
	{
		cellMapDimension = 100.0f;
	}
	else if (cellMapDimension > 50.0f && cellMapDimension < 100.0f)
	{
		cellMapDimension = 50.0f;
	}
	else if (cellMapDimension > 20.0f && cellMapDimension < 50.0f)
	{
		cellMapDimension = 20.0f;
	}
	else if (cellMapDimension < 10.0f)
	{
		cellMapDimension = 10.0f;
	}
	std::cout << "Decrease Button Clicked: Grid dimensions - " << cellMapDimension << " x " << cellMapDimension << std::endl;
	
}

void UIHandler::IncreaseTimeStep()
{
	timeStep += 0.01f;
	if (timeStep > 0.2f)
	{
		timeStep = 0.2f;
	}
	std::cout << "Increase Timestep Button Clicked: New Timestep - " << timeStep * 1000.0f << "ms" << std::endl;
}

void UIHandler::DecreaseTimeStep()
{
	timeStep -= 0.01f;
	if (timeStep < 0.01f)
	{
		timeStep = 0.01f;
	}
	std::cout << "Decrease Timestep Button Clicked: New Timestep - " << timeStep * 1000.0f << "ms" << std::endl;
}