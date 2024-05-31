#include "AudioManager.h"

AudioManager* AudioManager::m_instance;

void AudioManager::SetupManager()
{
	a_backgroundMusic = new Audio(AUPATH_BACKGROUND_MUSIC, 1);
	a_backgroundMusic->SetVolume(10);

	a_coinCollect = new Audio(AUPATH_COIN_COLLECT, 2);
	a_coinCollect->SetVolume(5);
}

AudioManager::AudioManager()
{

}
