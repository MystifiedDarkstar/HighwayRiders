#include "GameScreenManager.h"

#include "GameOverScreen.h"
#include "GameScreen.h"

#include "GameScreenLevel1.h"
#include "GameTitleScreen.h"
#include "CarCustomisationScreen.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	SaveGame::Instance().LoadSaveData();
	ChangeScreen(startScreen);

}
GameScreenManager::~GameScreenManager()
{
	SaveGame::Instance().WriteSaveData();
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}
void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime , e);

	switch (e.type)
	{
	case SDL_KEYUP: 
		Keyboard(e);
		break;
	case SDL_USEREVENT:
		if (e.user.code == 2)
		{
			ChangeScreen(SCREEN_GAMEOVER);
		}
		break;
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 2:
			if (m_currentScreenState == SCREEN_TITLE)
				ChangeScreen(SCREEN_CUSTOMISATION);
			break;
		case 3:
			if (m_currentScreenState == SCREEN_GAMEOVER)
				ChangeScreen(SCREEN_TITLE);
			else if (m_currentScreenState == SCREEN_TITLE)
				ChangeScreen(SCREEN_LEVEL1);
			break;
		case 17:
			if (m_currentScreenState == SCREEN_TITLE)
				SDL_Quit();
			else if (m_currentScreenState == SCREEN_CUSTOMISATION)
				ChangeScreen(SCREEN_TITLE);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	
	m_currentScreenState = new_screen;

	// CLEAR UP OLD SCREEN
	if (m_current_screen != nullptr)
	{
 		delete m_current_screen;
	}

	GameTitleScreen* gameTitleTempScreen;
	GameOverScreen* gameOverTempScreen;
	GameScreenLevel1* level1TempScreen;
	CarCustomisationScreen* customisationTempScreen;

	switch (new_screen)
	{
	case SCREEN_TITLE:
		gameTitleTempScreen = new GameTitleScreen(m_renderer);
		m_current_screen = (GameScreen*)gameTitleTempScreen;
		gameTitleTempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		level1TempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)level1TempScreen;
		level1TempScreen = nullptr;
		break;
	case SCREEN_GAMEOVER:
		gameOverTempScreen = new GameOverScreen(m_renderer);
		m_current_screen = (GameScreen*)gameOverTempScreen;
		gameOverTempScreen = nullptr;
		break;
	case SCREEN_CUSTOMISATION:
		customisationTempScreen = new CarCustomisationScreen(m_renderer);
		m_current_screen = (GameScreen*)customisationTempScreen;
		customisationTempScreen = nullptr;
	default:
		break;
	}
}

void GameScreenManager::Keyboard(SDL_Event e)
{
	switch (e.key.keysym.sym)
	{
		// SPACE KEY PRESSED
	case SDLK_SPACE:
		if (m_currentScreenState == SCREEN_GAMEOVER)
			ChangeScreen(SCREEN_TITLE);
		else if (m_currentScreenState == SCREEN_TITLE)
			ChangeScreen(SCREEN_LEVEL1);
		else if (m_currentScreenState == SCREEN_CUSTOMISATION)
			ChangeScreen(SCREEN_TITLE);
		break;
	case SDLK_y:
		if (m_currentScreenState == SCREEN_TITLE)
			ChangeScreen(SCREEN_CUSTOMISATION);
		break;
	default: break;
	}
}


