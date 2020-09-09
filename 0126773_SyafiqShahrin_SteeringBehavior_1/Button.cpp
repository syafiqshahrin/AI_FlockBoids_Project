/*
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"
#include "UIHandler.h"
#include "Button.h"


template<typename T>
Button<T>::Button()
{
	Entity();
}
template<typename T>
Button<T>::Button(MeshObject* mesh, Shader* shader)
{
	Entity(mesh, shader);
}
template<typename T>
Button<T>::Button(MeshObject* mesh, Shader* shader, Entity* parent)
{
	Entity(mesh, shader, parent);
}
template<typename T>
void Button<T>::BindFunction(T* obj, void (T::*buttonFunction)())
{
	handler = obj;
	buttonFunctionPtr = buttonFunction;
}
template<typename T>
bool Button<T>::CheckInput(InputData& input)
{
	bool isClicked = false;
	float x1 = m_EntityTransform.Position.x - (1.0f * m_EntityTransform.Scale.x);
	float x2 = m_EntityTransform.Position.x + (1.0f * m_EntityTransform.Scale.x);

	float y1 = m_EntityTransform.Position.y - (1.0f * m_EntityTransform.Scale.y);
	float y2 = m_EntityTransform.Position.y + (1.0f * m_EntityTransform.Scale.y);
	if (input.mousePosition.x >= x1 && input.mousePosition.x <= x2)
	{
		if (input.mousePosition.y >= y1 && input.mousePosition.y <= y2)
		{
			isHover = true;
			//std::cout << "Inside Button Boundary" << std::endl;
			if (input.isLeftClicked)
			{
				isClicked = input.isLeftClicked;
				input.isLeftClicked = false;
				OnClick();
				//std::cout << "Button Clicked" << std::endl;
			}
		}
		else
		{
			isHover = false;
		}
	}
	else
	{
		isHover = false;
	}
	return isClicked;
}
template<typename T>
void Button<T>::OnClick()
{
	(handler->*(buttonFunctionPtr))();
}
*/
