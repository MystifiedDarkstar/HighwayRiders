#include "Audio.h"

Audio::Audio(std::string audioPath, int channel)
{
	LoadFromFile(audioPath);
	m_channel = channel;
}

Audio::~Audio()
{
	Mix_FreeChunk(m_audioChunk);
}

void Audio::LoadFromFile(std::string path)
{
	
	m_audioChunk = Mix_LoadWAV(path.c_str());
	std::cout << Mix_GetError() << std::endl;
}

void Audio::PlayFile(int loops)
{
	Mix_PlayChannel(m_channel, m_audioChunk, loops);
}

void Audio::PauseTrack()
{
	Mix_Pause(m_channel);
}

void Audio::SetVolume(int newVolume)
{
	Mix_Volume(m_channel, newVolume);
}
