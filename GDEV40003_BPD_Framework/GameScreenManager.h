#pragma once

#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "SDL.h"
#include "Commons.h"

class GameScreen;
class GameScreenLevel1;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);
	
	void Keyboard(SDL_Event e);


private:
	SDL_Renderer* m_renderer = nullptr;

	GameScreen* m_current_screen = nullptr;
	SCREENS m_currentScreenState;

};

#endif // !_GAMESCREENMANAGER_H