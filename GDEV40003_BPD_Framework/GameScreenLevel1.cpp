#include "GameScreenLevel1.h"
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	Camera::GetInstance()->ResetCamera();

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{

	delete m_character;
	m_character = nullptr;

	delete m_backgroundManager;
	m_backgroundManager = nullptr;

	delete m_levelTimerManager;
	m_levelTimerManager = nullptr;

	delete m_scoreManager;
	m_scoreManager = nullptr;

	delete m_scoreUIBox;
	m_scoreUIBox = nullptr;

	delete m_timeCoinUIBox;
	m_timeCoinUIBox = nullptr;

	delete m_level1GlobalVars;
	m_level1GlobalVars = nullptr;

	AudioManager::Instance().PauseBackgroundMusic();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// START GAME COUNTDOWN
	if (m_level1GlobalVars->g_isStartGame)
	{
		m_startCountdown -= deltaTime;

		if (m_startCountdown <= 0)
		{
			m_level1GlobalVars->g_isGameActive = true;

			m_level1GlobalVars->g_isStartGame = false;
		}
	}
	
	// UPDATE BACKGROUND MANAGER
	m_backgroundManager->Update(deltaTime, e);
	// UPDATE LEVEL MANAGER
	m_levelTimerManager->Update(deltaTime, e);
	// UPDATE SCORE MANAGER
	m_scoreManager->Update(deltaTime, e);
	// UPDATE CAMERA
	Camera::GetInstance()->Update(deltaTime);
	// UPDATE CHARACTER
	m_character->Update(deltaTime, e);

	m_lvl1ObjectSpawner->Update(deltaTime,e);
}

void GameScreenLevel1::Render()
{
	// DRAW THE BACKGROUND
	m_backgroundManager->Render();

	// UPDATE CHARACTER RENDER
	m_character->Render();


	m_timeCoinUIBox->Render(Vector2D(10,10), SDL_FLIP_NONE);
	m_scoreUIBox->Render(Vector2D(590, 10), SDL_FLIP_NONE);

	// UPDATE LEVEL TIMER MANANGER
	m_levelTimerManager->Render();

	m_scoreManager->Render();

	m_lvl1ObjectSpawner->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Intialise level 1 globals
	if (!m_level1GlobalVars)
		m_level1GlobalVars = new Level1Globals();

	if(!m_backgroundManager)
		m_backgroundManager = new BackgroundManager (m_renderer, m_level1GlobalVars);

	if(!m_character)
		m_character = new PlayerCharacter (m_renderer, TPATH_REDCAR, Vector2D(200, 256), m_level1GlobalVars, SaveGame::Instance().ReturnPlayerColour());

	if (!m_scoreManager)
		m_scoreManager = new ScoreManager(m_renderer, m_level1GlobalVars);

	if(!m_levelTimerManager)
		m_levelTimerManager = new LevelTimerManager(m_renderer, m_level1GlobalVars, m_scoreManager);

	if (!m_lvl1ObjectSpawner)
		m_lvl1ObjectSpawner = new Level1ObjectSpawnHandler(m_renderer, m_level1GlobalVars, m_character, m_scoreManager);

	// SET CAMERA TARGET
	Camera::GetInstance()->SetTarget(m_character->GetOrigin());

	AudioManager::Instance().SetupManager();
	AudioManager::Instance().PlayBackgroundMusic();

// UI AND SCORE

	//Setup Coin / Time UI Box
	m_timeCoinUIBox = new Texture2D(m_renderer);
	if (!m_timeCoinUIBox->LoadFromFile(TPATH_UI_LARGEBOX))
		std::cout << "ERROR: Failed to load image. Path: 'Assets/Images/T_UILargeBox.png'" << std::endl;

	//Setup Score UI Box
	m_scoreUIBox = new Texture2D(m_renderer);
	if (!m_scoreUIBox->LoadFromFile(TPATH_UI_LARGEBOX))
		std::cout << "ERROR: Failed to load image. Path: 'Assets/Images/T_UILargeBox.png'" << std::endl;

	return true;
}



