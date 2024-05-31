#pragma once
#ifndef _SAVEGAME_H
#define _SAVEGAME_H

#include "Constants.h"
#include "Commons.h"

class SaveGame
{
public:
	static inline SaveGame& Instance()
	{
		if (m_instance == nullptr)
			m_instance = new SaveGame();

		return *SaveGame::m_instance;
	}

	void LoadSaveData();
	void WriteSaveData();

	inline int GetLevelAllTime() { return m_levelAllTime; }
	inline int GetHighScore() { return m_highScore; }

	inline void SetLevelAllTime(int data) { m_levelAllTime = data; }
	inline void SetHighScore(int data) { m_highScore = data; }

	inline int GetLastGameLevelTime() { return m_lastGameLevelTime; }
	inline int GetLastGameScore() { return m_lastGameScore; }

	inline void SetLastGameLevelTime(int data) { m_lastGameLevelTime = data; }
	inline void SetLastGameScore(int data) { m_lastGameScore = data; }

	inline Colour ReturnPlayerColour() { return m_playerColour; }
	inline void SetPlayerColour(Colour data) { m_playerColour = data; }

private:
	SaveGame();
	static SaveGame* m_instance;

	int m_levelAllTime = 0;
	int m_highScore = 0; 
	
	int m_lastGameLevelTime = 0;
	int m_lastGameScore = 0;

	Colour m_playerColour;
};

#endif