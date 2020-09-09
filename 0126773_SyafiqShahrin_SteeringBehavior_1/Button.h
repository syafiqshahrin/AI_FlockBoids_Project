#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"
#include "UIHandler.h"
#include "Entity.h"
#include "Button.h"

struct Transform;
template<typename T>
class Button : public Entity
{
public:
	Button();
	Button(MeshObject* mesh, Shader* shader);
	Button(MeshObject* mesh, Shader* shader, Entity* parent);
	void BindFunction(T* obj, void (T::*buttonFunction)());
	bool CheckInput(InputData& input);
	void OnClick();
	//
	T* handler;
	bool isHover = false;
	//
	
private:
	void (T::*buttonFunctionPtr)();
};

template<typename T>
Button<T>::Button() : Entity()
{

}
template<typename T>
Button<T>::Button(MeshObject* mesh, Shader* shader) : Entity(mesh, shader)
{

}
template<typename T>
Button<T>::Button(MeshObject* mesh, Shader* shader, Entity* parent) : Entity(mesh, shader, parent)
{

}
template<typename T>
void Button<T>::BindFunction(T* obj, void (T::* buttonFunction)())
{
	handler = obj;
	buttonFunctionPtr = buttonFunction;
}
template<typename T>
bool Button<T>::CheckInput(InputData& input)
{
	bool isClicked = false;
	float x1;
	float x2;
	float y1;
	float y2;
	
	
	if (Parent != nullptr)
	{
		Vector4 newPos = Parent->OrthoModelMatrix * Vector4(m_EntityTransform.Position.x, m_EntityTransform.Position.y, 0.0f, 1.0f);
		x1 = (newPos.x) - (1.0f * (m_EntityTransform.Scale.x * Parent->m_EntityTransform.Scale.x));
		x2 = (newPos.x) + (1.0f * (m_EntityTransform.Scale.x * Parent->m_EntityTransform.Scale.x));

		y1 = (newPos.y) - (1.0f * (m_EntityTransform.Scale.y * Parent->m_EntityTransform.Scale.y));
		y2 = (newPos.y) + (1.0f * (m_EntityTransform.Scale.y * Parent->m_EntityTransform.Scale.y));
	}
	else
	{
		x1 = m_EntityTransform.Position.x - (1.0f * m_EntityTransform.Scale.x);
		x2 = m_EntityTransform.Position.x + (1.0f * m_EntityTransform.Scale.x);

		y1 = m_EntityTransform.Position.y - (1.0f * m_EntityTransform.Scale.y);
		y2 = m_EntityTransform.Position.y + (1.0f * m_EntityTransform.Scale.y);
	}

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