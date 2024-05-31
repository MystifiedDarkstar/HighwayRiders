#pragma once
#ifndef _SCOREMANAGER_H
#define _SCOREMANAGER_H

#include <SDL.h>
#include "GUIText.h"
#include "Level1Globals.h"
#include "Constants.h"
#include "SaveGame.h"
#include <fstream>
#include <iostream>

class ScoreManager
{
public:
	ScoreManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals);
	~ScoreManager();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void AddCoin();
	void AddLevelTime(float deltaTime);

private:
	void SetUpManager();
	void CheckHighScore();

private:
	SDL_Renderer* m_renderer;
	Level1Globals* m_lvl1Globals;

	GUIText* m_scoreText;

	int m_totalCoinCount = 0;

	float m_timer = 0;

	int m_score = 0;
};

#endif
