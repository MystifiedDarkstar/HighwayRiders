#include "Level1ObjectSpawnHandler.h"

Level1ObjectSpawnHandler::Level1ObjectSpawnHandler(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player, ScoreManager* scoreMan)
{
	m_renderer = renderer;
	m_lvl1Globals = lvl1Globals;
	m_player = player;
	m_scoreManager = scoreMan;

	SetUpManager();
}

Level1ObjectSpawnHandler::~Level1ObjectSpawnHandler()
{
	delete m_obstacleManager;
	m_obstacleManager = nullptr;

	delete m_coinManager;
	m_coinManager = nullptr;

	delete m_powerUpManager;
	m_powerUpManager = nullptr;
}

void Level1ObjectSpawnHandler::Render()
{
	m_obstacleManager->Render();
	m_coinManager->Render();
	m_powerUpManager->Render();
}

void Level1ObjectSpawnHandler::Update(float deltaTime, SDL_Event e)
{
	m_obstacleManager->Update(deltaTime, e);
	m_coinManager->Update(deltaTime, e);
	m_powerUpManager->Update(deltaTime, e);

	m_freeSpawnLane = m_obstacleManager->ReturnFreeSpawnLane();

	if (m_lvl1Globals->g_isGameActive)
	{
		// decrement active timers
		m_currentObstacleSpawnTimer -= deltaTime;
		m_currentPickupSpawnTimer -= deltaTime;
		m_currentPowerUpSpawnTimer -= deltaTime;

		// check if timers are less than 0
		if (m_currentObstacleSpawnTimer <= 0)
		{
			m_obstacleManager->SpawnObstacles();
			m_currentObstacleSpawnTimer = m_maxObstacleSpawnTimer;
		}
		if (m_currentPickupSpawnTimer <= 0 && m_currentObstacleSpawnTimer >= 0.1f && m_currentObstacleSpawnTimer <= (m_maxObstacleSpawnTimer - 0.1f))
		{
			// check if we can spawn a pickup
			if (m_currentPowerUpSpawnTimer <= 0)
			{
				m_powerUpManager->SpawnPowerUp(m_freeSpawnLane);
				m_currentPowerUpSpawnTimer = m_maxPowerUpSpawnTimer;
			}
			// else spawn coin
			else
			{
				m_coinManager->SpawnCoin(m_freeSpawnLane);
			}
			m_currentPickupSpawnTimer = m_maxPickupSpawnTimer;
		}

		// CHECK FOR DIFFICULTY UPDATES
		switch (m_lvl1Globals->g_gameDifficulty)
		{
		case 1:
			m_maxObstacleSpawnTimer = 1.9f;
			m_obstacleManager->SetMinObstacles(2);
			break;
		case 2:
			m_maxObstacleSpawnTimer = 1.8f;
			m_maxPickupSpawnTimer = 0.25f;
			break;
		case 3:
			m_maxObstacleSpawnTimer = 1.7f;
			m_maxPowerUpSpawnTimer = 13.0f;
			m_obstacleManager->SetMaxObstacles(3);
			break;
		case 4:
			m_maxObstacleSpawnTimer = 1.6f;
			m_maxPickupSpawnTimer = 0.2f;
			m_obstacleManager->SetMinObstacles(3);
			break;
		case 5:
			m_maxObstacleSpawnTimer = 1.5f;
			m_maxPowerUpSpawnTimer = 10.0f;
			break;
		case 6:
			m_maxObstacleSpawnTimer = 1.4f;
			m_maxPickupSpawnTimer = 0.15f;
			break;
		default:
			std::cout << "ERROR: Difficulty Not Recognised!" << std::endl;
			break;
		}
	}
}

/// <summary>
/// Initialise all the member variables required for this class to run, such as other managers required to spawn obstacles, coins, and powerups.
/// </summary>
void Level1ObjectSpawnHandler::SetUpManager()
{
	m_obstacleManager = new ObstacleManager(m_renderer, m_lvl1Globals, m_player );
	m_coinManager = new CoinManager( m_renderer, m_lvl1Globals, m_player, m_scoreManager );
	m_powerUpManager = new PowerUpManager( m_renderer, m_lvl1Globals, m_player );

	m_currentPowerUpSpawnTimer = m_maxPowerUpSpawnTimer;
}
