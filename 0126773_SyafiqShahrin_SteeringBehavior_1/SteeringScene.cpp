#include <glad/glad.h>
#include <glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
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

SteeringScene::SteeringScene(int* wH, int* wW, float* dTime)
{
	deltatime = dTime;
	Init();
}

SteeringScene::~SteeringScene()
{

}
void SteeringScene::Init()
{

	LoadTextures();
	LoadShaders();
	CreateMeshes();
	CreateEntities();

}
void SteeringScene::LoadTextures()
{


}
void SteeringScene::LoadShaders()
{
	basicShader = Shader("../Shader/basicColVert.vert", "../Shader/basicColFrag.frag");
	basicCircleShader = Shader("../Shader/basicCircleVert.vert", "../Shader/basicCircleFrag.frag");

}
void SteeringScene::CreateMeshes()
{
	meshQuad = new MeshObject(QUAD);
	meshTriangle = new MeshObject(TRIANGLE);
}
void SteeringScene::CreateEntities()
{
	Attractor = Entity(meshQuad, &basicShader);
	Attractor.RotateEntity(45.0f, Vector3(0.0f, 0.0f, 1.0f));
	Attractor.ScaleEntity(Vector3(0.2f, 0.2f, 0.2f));
	Attractor.TranslateEntity(Vector3(0.0f, 0.0f, 0.0f));

	Predator = Entity(meshTriangle, &basicShader);
	Predator.RotateEntity(0.0f, Vector3(0.0f, 0.0f, 1.0f));
	Predator.ScaleEntity(Vector3(predatorScale, predatorScale, 0.2f));
	Predator.TranslateEntity(Vector3(0.0f, 0.0f, 0.0f));
	float x, y;
	x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	pVelocity = Vector2(x, y);
	pVelocity = pVelocity.normalize(pVelocity) * 3.0f;

	obstacleRadius = 3.0f * obstalceScale;
	avoidanceRadius = 10.0f * scale;
	predatorAvoidanceRadius = 30.0f * predatorScale;


}
void SteeringScene::UpdateInput(InputData& input)
{
	MoveAttractor(input);
	if (input.clearObjects)
	{
		ClearObjects();
	}
	if (input.isRightClicked)
	{
		clickPoint.x = input.mousePosition.x;
		clickPoint.y = input.mousePosition.y;
		AddObstacle(clickPoint.x, clickPoint.y);
		input.isRightClicked = false;
	}
	if (input.isLeftClicked)
	{

		clickPoint.x = input.mousePosition.x;
		clickPoint.y = input.mousePosition.y;
		AddOSteeringObject(clickPoint.x, clickPoint.y);
		input.isLeftClicked = false;
	}
	

	//st = glfwGetTime() - st;
	//std::cout << "Check Grid Time: " << st * 1000 << std::endl;
}
void SteeringScene::UpdateScene()
{
	//float st = glfwGetTime();
	UpdateFlock();
	UpdatePredator();

	//st = glfwGetTime() - st;
	//std::cout << "Update Scene Time: " << st * 1000 << std::endl;
}
void SteeringScene::DrawScene()
{
	float st = glfwGetTime();
	Vector3 white = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 red = Vector3(0.8f, 0.0f, 0.0f);
	Vector3 green = Vector3(0.0f, 0.8f, 0.2f);
	Vector3 blue = Vector3(0.0f, 0.5f, 0.9f);
	if (flockSize > 0)
	{
		steeringObject[0].m_meshShader->use();
		steeringObject[0].m_meshShader->setVec3("Color", green.x, green.y, green.z);
		for (int i = 0; i < flockSize; i++)
		{
			steeringObject[i].DrawEntity(0);
		}
	}
	if (obstacleAmount > 0)
	{
		obstacle[0].m_meshShader->use();
		obstacle[0].m_meshShader->setVec3("Color", white.x, white.y, white.z);
		for (int i = 0; i < obstacleAmount; i++)
		{
			obstacle[i].DrawEntity(0);
		}
	}


	Attractor.m_meshShader->use();
	Attractor.m_meshShader->setVec3("Color", blue.x, blue.y, blue.z);
	Attractor.DrawEntity(0);
	Predator.m_meshShader->use();
	Predator.m_meshShader->setVec3("Color", red.x, red.y, red.z);
	Predator.DrawEntity(0);

	
	st = glfwGetTime() - st;
	//std::cout << "Draw Scene Time: " << st * 1000 << std::endl;
}

void SteeringScene::UpdateFlock()
{
	float speed = 3.0f;
	float aspectRatio = 1600.0f / 1000.0f;
	float maxX = aspectRatio * 10.0f;
	float minX = aspectRatio * -10.0f;
	float maxY = 10.0f;
	float minY = -10.0f;
	Vector2 target;
	target.x = Attractor.m_EntityTransform.Position.x;
	target.y = Attractor.m_EntityTransform.Position.y;
	//CheckFOV(0, 1);
	for (int i = 0; i < flockSize; i++)
	{

		SeekAI(i, target);
		SpreadAI(i);
		AlignAI(i);
		GroupAI(i);
		CheckObtacles(i);
		CheckPredator(i);
		velocity[i] = velocity[i] + targetVec[i] + avoidanceVec[i] + alignmentVec[i] + cohesionVec[i] + obstacleAvoidanceVec[i] + predatorAvoidanceVec[i];
		float velocityMagnitude = velocity[i].length(velocity[i]);
		//std::cout << velocityMagnitude << std::endl;
		if (velocityMagnitude > speed)
		{
			velocity[i] = velocity[i].normalize(velocity[i]) * speed;
		}
		steeringObject[i].m_EntityTransform.Position.x += (velocity[i].x) * *deltatime;
		steeringObject[i].m_EntityTransform.Position.y += (velocity[i].y) * *deltatime;
		UpdateAIRotation(i);

		// boundary wrapping
		if (steeringObject[i].m_EntityTransform.Position.x > maxX)
		{
			steeringObject[i].m_EntityTransform.Position.x = minX;
		}
		else if (steeringObject[i].m_EntityTransform.Position.x < minX)
		{
			steeringObject[i].m_EntityTransform.Position.x = maxX;
		}

		if (steeringObject[i].m_EntityTransform.Position.y > maxY)
		{
			steeringObject[i].m_EntityTransform.Position.y = minY;
		}
		else if (steeringObject[i].m_EntityTransform.Position.y < minY)
		{
			steeringObject[i].m_EntityTransform.Position.y = maxY;
		}


	}
}

void SteeringScene::SeekAI(int i, Vector2 target)
{
	float weight = 5.0f;

	Vector2 objectPos = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
	targetVec[i] = target - objectPos;
	targetVec[i] = targetVec[i].normalize(targetVec[i]) * weight * *deltatime;

	
}

void SteeringScene::SpreadAI(int i)
{
	float weight = 15.0f;


	Vector2 steerObject;
	steerObject = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
	avoidanceVec[i] = Vector2(0.0f, 0.0f);
	for (int j = 0; j < flockSize; j++)
	{

			
		if (j != i)
		{
			Vector2 otherSteerObject;
			otherSteerObject = Vector2(steeringObject[j].m_EntityTransform.Position.x, steeringObject[j].m_EntityTransform.Position.y);
			Vector2 avoidDirection = steerObject - otherSteerObject;
			float distance = avoidDirection.length(avoidDirection);
			if (distance < avoidanceRadius)
			{
		
				if(CheckAvoidanceFOV(i,j))
				{
					//std::cout << "Avoid!" << std::endl;
					avoidanceVec[i] = avoidanceVec[i] + (avoidDirection.normalize(avoidDirection));
				}
				
			}
		}
	}
	avoidanceVec[i] = avoidanceVec[i].normalize(avoidanceVec[i]) * weight * *deltatime;
	
}

void SteeringScene::AlignAI(int i)
{
	float weight = 10.0f;


	Vector2 steerObject;
	steerObject = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
	alignmentVec[i] = Vector2(0.0f, 0.0f);
	int neighbours = 0;
	for (int j = 0; j < flockSize; j++)
	{
		if (j != i)
		{

			Vector2 otherSteerObject;
			otherSteerObject = Vector2(steeringObject[j].m_EntityTransform.Position.x, steeringObject[j].m_EntityTransform.Position.y);
			Vector2 avoidDirection = steerObject - otherSteerObject;
			float distance = avoidDirection.length(avoidDirection);
			if (distance < avoidanceRadius * 2)
			{
				if (CheckFOV(i, j))
				{
					//std::cout << "Align!" << std::endl;
					alignmentVec[i] = alignmentVec[i] + velocity[j].normalize(velocity[j]);
					neighbours += 1;
				}
				
			}
		}
	}
	alignmentVec[i] = alignmentVec[i] / neighbours;
	alignmentVec[i] = alignmentVec[i].normalize(alignmentVec[i]) * weight * *deltatime;
		
	
}

void SteeringScene::GroupAI(int i)
{
	float weight = 5.0f;
	
	Vector2 steerObject;
	steerObject = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
	cohesionVec[i] = Vector2(0.0f, 0.0f);
	int neighbours = 0;
	Vector2 avgPos = Vector2(0.0f, 0.0f);
	for (int j = 0; j < flockSize; j++)
	{
		if (j != i)
		{

			Vector2 otherSteerObject;
			otherSteerObject = Vector2(steeringObject[j].m_EntityTransform.Position.x, steeringObject[j].m_EntityTransform.Position.y);
			Vector2 avoidDirection = steerObject - otherSteerObject;
			float distance = avoidDirection.length(avoidDirection);
			if (distance < avoidanceRadius * 2)
			{

				if (CheckFOV(i, j))
				{
					avgPos = avgPos + otherSteerObject;
					neighbours += 1;
				}
			
			}

		}
	}
	if (neighbours > 0)
	{
		avgPos = avgPos / neighbours;
		cohesionVec[i] = avgPos - steerObject;
		cohesionVec[i] = cohesionVec[i].normalize(cohesionVec[i]) * weight * *deltatime;
	}
	
	

}

void SteeringScene::UpdateAIRotation(int i)
{
	float angle = atan2f(velocity[i].y, velocity[i].x);
	angle *= (180.0f/ M_PI);
	//std::cout << angle << std::endl;
	steeringObject[i].RotateEntity(angle, Vector3(0.0f, 0.0f, 1.0f));
}

bool SteeringScene::CheckAvoidanceFOV(int i, int j)
{
	if (!enableFOV)
	{
		return true;
	}
	Vector2 otherSteerObject;
	otherSteerObject = Vector2(steeringObject[j].m_EntityTransform.Position.x, steeringObject[j].m_EntityTransform.Position.y);
	//otherSteerObject = otherSteerObject.normalize(otherSteerObject);
	Vector4 otherVector = Vector4(otherSteerObject.x, otherSteerObject.y, 0.0f, 1.0f);
	//
	Matrix4 localmat = steeringObject[i].modelMatrix.invert(steeringObject[i].modelMatrix);
	Vector4 localOtherVector = localmat * otherVector;
	//std::cout << "x: " << localOtherVector.x << " y:" << localOtherVector.y <<   std::endl;
	//
	float otherAngle = atan2(localOtherVector.y, localOtherVector.x) * (180.0f / M_PI);
	otherAngle = ((int)otherAngle + 360) % 360;
	//std::cout << otherAngle << std::endl;

	if (!(otherAngle >= avoidanceLBoundary && otherAngle <= avoidanceHBoundary))
	{
		return true;
	}
	return false;
}

bool SteeringScene::CheckFOV(int i, int j)
{
	if (!enableFOV)
	{
		return true;
	}
	Vector2 otherSteerObject;
	otherSteerObject = Vector2(steeringObject[j].m_EntityTransform.Position.x, steeringObject[j].m_EntityTransform.Position.y);
	Vector4 otherVector = Vector4(otherSteerObject.x, otherSteerObject.y, 0.0f, 1.0f);
	//
	Matrix4 localmat = steeringObject[i].modelMatrix.invert(steeringObject[i].modelMatrix);
	Vector4 localOtherVector = localmat * otherVector;
	//std::cout << "x: " << localOtherVector.x << " y:" << localOtherVector.y <<   std::endl;
	//
	float otherAngle = atan2(localOtherVector.y, localOtherVector.x) * (180.0f / M_PI);
	otherAngle = ((int)otherAngle + 360) % 360;
	//std::cout << otherAngle << std::endl;
	
	if (!(otherAngle >= fovLBoundary && otherAngle <= fovHBoundary))
	{
		return true;
	}
	return false;
}

void SteeringScene::CheckObtacles(int i)
{
	float maxWeight = 25.0f;
	float baseWeight = 25.0f;
	float weight = 0.0f;
	obstacleAvoidanceVec[i] = Vector2(0.0f, 0.0f);
	for (int j = 0; j < obstacleAmount; j++)
	{
		Vector2 steerObjectPos = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
		Vector2 currentObstacle = Vector2(obstacle[j].m_EntityTransform.Position.x, obstacle[j].m_EntityTransform.Position.y);
		Vector2 avoidDirection = steerObjectPos - currentObstacle;
		float distanceToObstacle = avoidDirection.length(avoidDirection);
		if (distanceToObstacle < obstacleRadius)
		{
			weight = (obstacleRadius / distanceToObstacle) * maxWeight;
			obstacleAvoidanceVec[i] = obstacleAvoidanceVec[i] + (avoidDirection.normalize(avoidDirection * weight) );
		}
		obstacleAvoidanceVec[i] = obstacleAvoidanceVec[i].normalize(obstacleAvoidanceVec[i]) * baseWeight * *deltatime;
	}
}

void SteeringScene::CheckPredator(int i)
{
	float maxWeight = 10.0f;
	float baseWeight = 10.0f;
	float weight = 0.0f;
	predatorAvoidanceVec[i] = Vector2(0.0f, 0.0f);
	Vector2 steerObjectPos = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
	Vector2 predator = Vector2(Predator.m_EntityTransform.Position.x, Predator.m_EntityTransform.Position.y);
	Vector2 avoidDirection = steerObjectPos - predator;
	float distanceToObstacle = avoidDirection.length(avoidDirection);
	if (distanceToObstacle < predatorAvoidanceRadius)
	{
		weight = (obstacleRadius / distanceToObstacle) * maxWeight;
		predatorAvoidanceVec[i] = predatorAvoidanceVec[i] + (avoidDirection.normalize(avoidDirection * weight));
	}
	predatorAvoidanceVec[i] = predatorAvoidanceVec[i].normalize(predatorAvoidanceVec[i]) * baseWeight * *deltatime;
	
}

void SteeringScene::AddObstacle(float x, float y)
{
	obstacleAmount++;
	obstacle.push_back(Entity(meshQuad, &basicCircleShader));
	obstacle[obstacleAmount - 1].ScaleEntity(Vector3(obstalceScale, obstalceScale, 1.0f));
	obstacle[obstacleAmount - 1].TranslateEntity(Vector3(x, y, 0.0f));
}

void SteeringScene::AddOSteeringObject(float x, float y)
{
	flockSize++;
	velocity.push_back(Vector2(0.0f, 0.0f));
	targetVec.push_back(Vector2(0.0f, 0.0f));
	avoidanceVec.push_back(Vector2(0.0f, 0.0f));
	cohesionVec.push_back(Vector2(0.0f, 0.0f));
	alignmentVec.push_back(Vector2(0.0f, 0.0f));
	obstacleAvoidanceVec.push_back(Vector2(0.0f, 0.0f));
	predatorAvoidanceVec.push_back(Vector2(0.0f, 0.0f));
	steeringObject.push_back(Entity(meshTriangle, &basicShader));
	steeringObject[flockSize - 1].ScaleEntity(Vector3(scale, scale, 1.0f));
	steeringObject[flockSize - 1].TranslateEntity(Vector3(x, y, 0.0f));
	x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	velocity[flockSize -1] = Vector2(x, y);
	velocity[flockSize - 1] = velocity[flockSize - 1].normalize(velocity[flockSize - 1]) * 3.0f;

}

void SteeringScene::MoveAttractor(InputData& input)
{
	float aspectRatio = 1600.0f / 1000.0f;
	float maxX = aspectRatio * 10.0f;
	float minX = aspectRatio * -10.0f;
	float maxY = 10.0f;
	float minY = -10.0f;
	if (input.UpButtonPressed)
	{
		Vector3 newPos = Vector3(Attractor.m_EntityTransform.Position.x, Attractor.m_EntityTransform.Position.y + (1.0f * attractorSpeed * *deltatime), Attractor.m_EntityTransform.Position.z);
		Attractor.TranslateEntity(newPos);
	}
	if (input.DownButtonPressed)
	{
		Vector3 newPos = Vector3(Attractor.m_EntityTransform.Position.x, Attractor.m_EntityTransform.Position.y - (1.0f * attractorSpeed * *deltatime), Attractor.m_EntityTransform.Position.z);
		Attractor.TranslateEntity(newPos);
	}
	if (input.LeftButtonPressed)
	{
		Vector3 newPos = Vector3(Attractor.m_EntityTransform.Position.x - (1.0f * attractorSpeed * *deltatime), Attractor.m_EntityTransform.Position.y, Attractor.m_EntityTransform.Position.z);
		Attractor.TranslateEntity(newPos);
	}
	if (input.RightButtonPressed)
	{
		Vector3 newPos = Vector3(Attractor.m_EntityTransform.Position.x + (1.0f * attractorSpeed * *deltatime), Attractor.m_EntityTransform.Position.y, Attractor.m_EntityTransform.Position.z);
		Attractor.TranslateEntity(newPos);
	}
	if (Attractor.m_EntityTransform.Position.x > maxX)
	{
		Attractor.m_EntityTransform.Position.x = minX;
	}
	else if (Attractor.m_EntityTransform.Position.x < minX)
	{
		Attractor.m_EntityTransform.Position.x = maxX;
	}

	if (Attractor.m_EntityTransform.Position.y > maxY)
	{
		Attractor.m_EntityTransform.Position.y = minY;
	}
	else if (Predator.m_EntityTransform.Position.y < minY)
	{
		Attractor.m_EntityTransform.Position.y = maxY;
	}
}

void SteeringScene::ClearObjects()
{
	flockSize = 0;
	velocity.clear();
	targetVec.clear();
	avoidanceVec.clear();
	cohesionVec.clear();
	alignmentVec.clear();
	obstacleAvoidanceVec.clear();
	predatorAvoidanceVec.clear();
	steeringObject.clear();


	obstacleAmount = 0;
	obstacle.clear();
}

void SteeringScene::UpdatePredator()
{
	float speed = 2.5f;
	float aspectRatio = 1600.0f / 1000.0f;
	float maxX = aspectRatio * 10.0f;
	float minX = aspectRatio * -10.0f;
	float maxY = 10.0f;
	float minY = -10.0f;
	PredatorSeek();
	PredatorCheckObtacles();
	
	pVelocity = pVelocity + pTargetVec + pObstacleAvoidanceVec;
	float velocityMagnitude = pVelocity.length(pVelocity);
	//std::cout << velocityMagnitude << std::endl;
	if (velocityMagnitude > speed)
	{
		pVelocity = pVelocity.normalize(pVelocity) * speed;
	}
	Predator.m_EntityTransform.Position.x += (pVelocity.x) * *deltatime;
	Predator.m_EntityTransform.Position.y += (pVelocity.y) * *deltatime;
	PredatorUpdateRotation();

	if (Predator.m_EntityTransform.Position.x > maxX)
	{
		Predator.m_EntityTransform.Position.x = minX;
	}
	else if (Predator.m_EntityTransform.Position.x < minX)
	{
		Predator.m_EntityTransform.Position.x = maxX;
	}

	if (Predator.m_EntityTransform.Position.y > maxY)
	{
		Predator.m_EntityTransform.Position.y = minY;
	}
	else if (Predator.m_EntityTransform.Position.y < minY)
	{
		Predator.m_EntityTransform.Position.y = maxY;
	}
}

void SteeringScene::PredatorSeek()
{
	if (flockSize > 0)
	{
		float weight = 10.0f;
		Vector2 avgPos = Vector2(0.0f, 0.0f);
		Vector2 currentPos = Vector2(Predator.m_EntityTransform.Position.x, Predator.m_EntityTransform.Position.y);
		for (int i = 0; i < flockSize; i++)
		{
			Vector2 currentSteerObject = Vector2(steeringObject[i].m_EntityTransform.Position.x, steeringObject[i].m_EntityTransform.Position.y);
			avgPos = avgPos + currentSteerObject;
		}
		avgPos = avgPos / flockSize;
		pTargetVec = avgPos - currentPos;
		pTargetVec = pTargetVec.normalize(pTargetVec) * weight * *deltatime;
	}

}

void SteeringScene::PredatorCheckObtacles()
{
	float maxWeight = 25.0f;
	float baseWeight = 25.0f;
	float weight = 0.0f;
	pObstacleAvoidanceVec = Vector2(0.0f, 0.0f);
	for (int j = 0; j < obstacleAmount; j++)
	{
		Vector2 predator = Vector2(Predator.m_EntityTransform.Position.x, Predator.m_EntityTransform.Position.y);
		Vector2 currentObstacle = Vector2(obstacle[j].m_EntityTransform.Position.x, obstacle[j].m_EntityTransform.Position.y);
		Vector2 avoidDirection = predator - currentObstacle;
		float distanceToObstacle = avoidDirection.length(avoidDirection);
		if (distanceToObstacle < obstacleRadius)
		{
			weight = (obstacleRadius / distanceToObstacle) * maxWeight;
			pObstacleAvoidanceVec = pObstacleAvoidanceVec + (avoidDirection.normalize(avoidDirection * weight));
		}
		pObstacleAvoidanceVec = pObstacleAvoidanceVec.normalize(pObstacleAvoidanceVec) * baseWeight * *deltatime;
	}
}

void SteeringScene::PredatorUpdateRotation()
{
	float angle = atan2f(pVelocity.y, pVelocity.x);
	angle *= (180.0f / M_PI);
	//std::cout << angle << std::endl;
	Predator.RotateEntity(angle, Vector3(0.0f, 0.0f, 1.0f));
}

