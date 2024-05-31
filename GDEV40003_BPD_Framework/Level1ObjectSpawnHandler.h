#pragma once
#ifndef _PICKUPSPAWNHANDLER_H
#define _PICKUPSPAWNHANDLER_H

#include "SDL.h"
#include "Level1Globals.h"
#include "CoinManager.h"
#include "ObstacleManager.h"
#include "PlayerCharacter.h"
#include "PowerUpManager.h"
#include "ScoreManager.h"

/// <summary>
/// This class deals with running timers for when to spawn obstacles, coins, and power ups into the world. Spawning is handled by seperate management classes.
/// </summary>
class Level1ObjectSpawnHandler
{
public:
	Level1ObjectSpawnHandler(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player, ScoreManager* scoreMan);
	~Level1ObjectSpawnHandler();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	void SetUpManager();

private:
	SDL_Renderer* m_renderer = nullptr;
	Level1Globals* m_lvl1Globals = nullptr;

	PlayerCharacter* m_player = nullptr;
	ScoreManager* m_scoreManager = nullptr;

	ObstacleManager* m_obstacleManager;
	CoinManager* m_coinManager;
	PowerUpManager* m_powerUpManager;

	float m_maxObstacleSpawnTimer = 2.0f;
	float m_maxPickupSpawnTimer = 0.3f; 
	float m_maxPowerUpSpawnTimer = 15.0f; 

	float m_currentObstacleSpawnTimer = 0.3;
	float m_currentPickupSpawnTimer;
	float m_currentPowerUpSpawnTimer;

	float m_freeSpawnLane = 0;
};

#endif