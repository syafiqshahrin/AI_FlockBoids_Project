#pragma once


class Scene
{
public:
	virtual void DrawScene() = 0;
	virtual void UpdateScene() = 0;
	virtual void UpdateInput(InputData &input) = 0;
private:
	virtual void Init() = 0;
	virtual void LoadShaders() = 0;
	virtual void LoadTextures() = 0;
	virtual void CreateMeshes() = 0;
	virtual void CreateEntities() = 0;
};