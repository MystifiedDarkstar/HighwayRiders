#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Level1Globals.h"
#include "Commons.h"
#include "Constants.h"
#include "Level1ObjectSpawnHandler.h"
#include "LevelTimerManager.h"
#include "BackgroundManager.h"
#include "ScoreManager.h"
#include "PlayerCharacter.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "Camera.h"
#include "AudioManager.h"
#include "SaveGame.h"


class Texture2D;
class PlayerCharacter;
class Level1Globals;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1() override;

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpLevel();

private: 
	Level1Globals* m_level1GlobalVars = nullptr;

	LevelTimerManager* m_levelTimerManager = nullptr;
	BackgroundManager* m_backgroundManager = nullptr;
	ScoreManager* m_scoreManager = nullptr;
	Level1ObjectSpawnHandler* m_lvl1ObjectSpawner = nullptr;

	PlayerCharacter* m_character = nullptr;

	Texture2D* m_timeCoinUIBox = nullptr;
	Texture2D* m_scoreUIBox = nullptr;

	bool m_IsStartGame = true;
	float m_startCountdown = 3.0f;
};

#endif // _GAMESCREENLEVEL1_H
