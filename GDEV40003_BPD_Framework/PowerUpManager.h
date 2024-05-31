#pragma once

#ifndef _POWERUPMANAGER_H
#define _POWERUPMANAGER_H

#include "SDL.h"
#include "Constants.h"
#include <vector>
#include "Level1Globals.h"
#include "PowerUp.h"
#include "PlayerCharacter.h"
#include "GUIText.h"

class PowerUpManager
{
public:
	PowerUpManager(SDL_Renderer* renderer, Level1Globals* level1Globals, PlayerCharacter* player);
	~PowerUpManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SpawnPowerUp(int lane);

private:
	void SetUpManager();

	void ExecutePowerUp(PowerUps powerUPType);
	void RemovePowerUpObject(int index);

private:

	SDL_Renderer* m_renderer = nullptr;
	Level1Globals* m_lvl1Globals = nullptr;
	PlayerCharacter* m_player = nullptr;
	GUIText* m_powerUpInfo = nullptr;

	std::vector <PowerUp*> m_currentPowerUpsVector;

	PowerUps m_activePowerUPType = NONE;
	bool m_isActivePowerUP = false;
	float m_activePowerUPTimer;

	float m_defaultPowerUpTimer = 5.0f;
};

#endif
