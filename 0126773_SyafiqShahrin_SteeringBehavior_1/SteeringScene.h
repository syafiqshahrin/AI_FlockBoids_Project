#pragma once
#include "Scene.h"

class Shader;
class MeshObject;
class Entity;

class UIHandler;

class SteeringScene : Scene
{
public:
	SteeringScene(int* wH, int* wW, float* dTime);
	~SteeringScene();
	void DrawScene();
	void UpdateInput(InputData& input);
	void UpdateScene();


private:
	void Init();
	void LoadTextures();
	void LoadShaders();
	void CreateMeshes();
	void CreateEntities();

	void SeekAI(int i,Vector2 target);

	void SpreadAI(int i);
	void AlignAI(int i);
	void GroupAI(int i);
	void UpdateAIRotation(int i);
	void UpdateFlock();
	bool CheckAvoidanceFOV(int i, int j);
	bool CheckFOV(int i, int j);
	void CheckObtacles(int i);
	void CheckPredator(int i);

	void AddObstacle(float x, float y);
	void AddOSteeringObject(float x, float y);
	void MoveAttractor(InputData& input);
	void ClearObjects();

	void PredatorSeek();
	void PredatorCheckObtacles();
	void UpdatePredator();
	void PredatorUpdateRotation();
	//Textrures
	//GLuint textTextureID[12];



	//Meshes
	MeshObject* meshQuad;
	MeshObject* meshTriangle;


	//Entities
	unsigned int flockSize = 0;
	unsigned int obstacleAmount = 0;
	std::vector<Entity> steeringObject;
	//Entity steeringObject[flockSize];
	std::vector<Entity> obstacle;
	//Entity obstacle[2];
	Entity Attractor;
	Entity Predator;
	



	//Shaders
	Shader basicShader;
	Shader basicCircleShader;


	///Steering/Boids stuff
	float* deltatime;

	//Flock 
	std::vector<Vector2> velocity;
	std::vector<Vector2> targetVec;
	std::vector<Vector2> avoidanceVec;
	std::vector<Vector2> cohesionVec;
	std::vector<Vector2> alignmentVec;
	std::vector<Vector2> obstacleAvoidanceVec;
	std::vector<Vector2> predatorAvoidanceVec;

	//Predator
	Vector2 pVelocity;
	Vector2 pTargetVec;
	Vector2 pObstacleAvoidanceVec;

	Vector2 clickPoint;

	float scale = 0.1f;
	float obstalceScale = 0.5f;
	float predatorScale = 0.2f;

	float obstacleRadius;
	float avoidanceRadius;
	float predatorAvoidanceRadius;

	float avoidanceLBoundary = 180.0f - 15.0f;
	float avoidanceHBoundary = 180.0f + 15.0f;

	float fovLBoundary = 180.0f - 30.0f;
	float fovHBoundary = 180.0f + 30.0f;

	bool enableFOV = true;

	float attractorSpeed = 3.0f;
};