#pragma once


class UIHandler
{
public:
	bool isPlaying = false;
	bool clearMap = false;
	float cellMapDimension = 10.0f;
	float timeStep = 0.01f;
	void Play();
	void Clear();
	void IncreaseTimeStep();
	void DecreaseTimeStep();
	void DecreaseCellMapDimensions();
	void IncreaseCellMapDimensions();
};