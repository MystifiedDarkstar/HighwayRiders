#pragma once

#ifndef _GAMETITLESCREEN_H
#define _GAMETITLESCREEN_H

#include "GameScreen.h"
#include "Background.h"
#include "Commons.h"
#include "GUIText.h"
#include "SaveGame.h"
#include <fstream>

class Texture2D;

class GameTitleScreen : GameScreen
{
public:
	GameTitleScreen(SDL_Renderer* renderer);
	~GameTitleScreen() override;

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	
private:
	bool SetUpLevel();
	
private:
	Background* m_background = nullptr;
	Texture2D* m_menuText = nullptr;

	GUIText* m_timerText = nullptr;
	GUIText* m_scoreText = nullptr;

	int m_levelTimeAllTime = 0;
	int m_scoreAllTime = 0;

	Uint8 m_menuTextAlpha = 255;
	float m_menuTextAlphaFloat = 255;
};


#endif // !_GAMETITLESCREEN_H