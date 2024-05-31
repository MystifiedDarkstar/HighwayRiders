#pragma once
#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include "Constants.h"
#include "Audio.h"

class AudioManager
{
public:
	static inline AudioManager& Instance()
	{
		if (m_instance == nullptr)
			m_instance = new AudioManager();

		return *AudioManager::m_instance;
	}

	void SetupManager();

	void PlayBackgroundMusic() { a_backgroundMusic->PlayFile(-1); }
	void PauseBackgroundMusic() { a_backgroundMusic->PauseTrack(); }

	void PlayCoinCollect() { a_coinCollect->PlayFile(1); }
	void PauseCoinCollect() { a_coinCollect->PauseTrack(); }

private:
	AudioManager();
	static AudioManager* m_instance;

	Audio* a_backgroundMusic; // channel 1
	Audio* a_coinCollect; // channel 2
};

#endif // !_AUDIOMANAGER_H