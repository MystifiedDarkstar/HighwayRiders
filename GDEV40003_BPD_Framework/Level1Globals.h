#pragma once
#ifndef _LEVEL1GLOBALS_H
#define _LEVEL1GLOBALS_H

class Level1Globals
{
public:
	float g_scrollSpeedMultiplier = 1.0f;
	float g_scoreMultiplier = 1.0f;

	int g_gameDifficulty = 1;

	bool g_isGameActive = false;
	bool g_isStartGame = true;
};

#endif // !_LEVEL1GLOBALS_H

