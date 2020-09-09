#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "stb_image.h"
#include "Vector.h"
#include "Utility.h"



Transform::Transform()
{
	Position = Vector3(0.0f, 0.0f, 0.0f);
	RotationAxis = Vector3(0.0f, 0.0f, 0.0f);
	Scale = Vector3(1.0f, 1.0f, 1.0f);
	RotationAngle = 0.0f;
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale, float angle)
{
	Position = position;
	RotationAxis = rotation;
	Scale = scale;
	RotationAngle = angle;
}
InputData::InputData()
{
	mousePosition = Vector2(-1.0f, -1.0f);
	isLeftClicked = false;
	uiKeyToggle = true;
	mouseInWindow = false;
	clearObjects = false;

	UpButtonPressed = false;
	DownButtonPressed = false;
	LeftButtonPressed = false;
	RightButtonPressed = false;

	//
}
void Utility::loadTexturePNG(const char* path, GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Apply texture wrapping along horizontal part
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Apply texture wrapping along vertical part

	//old school (minecraft) filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when textures needs to scale up on screen)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when textures needs to scale down on screen)

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{

		std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
	}

	//glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}