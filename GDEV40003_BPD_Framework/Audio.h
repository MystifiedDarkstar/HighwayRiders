#pragma once
#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL_mixer.h>
#include <iostream>
#include <string>

class Audio
{
public:
	Audio(std::string audioPath, int channel);
	~Audio();

	void LoadFromFile(std::string path);
	void PlayFile(int loops);
	void PauseTrack();
	void SetVolume(int newVolume);

private:
	Mix_Chunk* m_audioChunk;
	int m_channel;
};

#endif
