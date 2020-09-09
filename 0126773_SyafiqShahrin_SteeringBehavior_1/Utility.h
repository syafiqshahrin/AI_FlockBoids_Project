#pragma once
struct Vector3;


class Utility
{
public:
	static void loadTexturePNG(const char* path, GLuint textureID);
};

struct Transform
{
	Vector3 Position;
	Vector3 RotationAxis;
	Vector3 Scale;
	float RotationAngle;

	Transform();
	Transform(Vector3 position, Vector3 rotation, Vector3 scale, float RotationAngle);
};

struct InputData
{
	Vector2 mousePosition;

	bool isLeftClicked;
	bool isRightClicked;
	bool uiKeyToggle;
	bool clearObjects;
	bool mouseInWindow;
	bool UpButtonPressed;
	bool DownButtonPressed;
	bool LeftButtonPressed;
	bool RightButtonPressed;
	//temporary (to be converted to buttons)
	//
	InputData();
};