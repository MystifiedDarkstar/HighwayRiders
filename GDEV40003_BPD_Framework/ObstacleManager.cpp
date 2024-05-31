#include "ObstacleManager.h"
#include "Camera.h"
#include "Collisions.h"
#include "MathFunctions.h"

ObstacleManager::ObstacleManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player)
{
    m_renderer = renderer;
    m_lvl1Globals = lvl1Globals;
    m_player = player;
}

ObstacleManager::~ObstacleManager()
{
    m_currentObstaclesVector.clear(); 
}

void ObstacleManager::Render()
{
    for (int i = 0; i < m_currentObstaclesVector.size(); i++)
    {
        m_currentObstaclesVector[i]->Render();
    }
}

void ObstacleManager::Update(float deltaTime, SDL_Event e)
{
    if (m_lvl1Globals->g_isGameActive)
    {

        // CHECK PLAYER / OBSTACLE COLLISION
        for (int i = 0; i < m_currentObstaclesVector.size(); i++)
        {
            if (Collisions::Instance()->Box(m_player->GetCollisionBox(), m_currentObstaclesVector[i]->GetCollisionBox()))
            {
                m_lvl1Globals->g_isGameActive = false;

                SDL_Event m_endGameEvent;
                m_endGameEvent.user.type = SDL_USEREVENT;
                m_endGameEvent.user.code = 2;
                SDL_PushEvent(&m_endGameEvent);
            }
        }
        
        // SCROLL OBSTACLE
        for (int i = 0; i < m_currentObstaclesVector.size(); i++)
        {
            Vector2D position = m_currentObstaclesVector[i]->GetPosition();
            position.x -= deltaTime * (SCROLL_SPEED * m_lvl1Globals->g_scrollSpeedMultiplier);
            m_currentObstaclesVector[i]->SetPosition(position);
        }

        // CHECK IF OBSTACLES ARE OUTSIDE CAMERA VIEW AND DELETE IF SO.
        int camXPos = Camera::GetInstance()->GetViewBox().x;

        for (int i = 0; i < m_currentObstaclesVector.size(); i++)
        {
            if (camXPos - m_currentObstaclesVector[i]->GetPosition().x > 200) 
            {
                delete m_currentObstaclesVector[i];
                auto itr = m_currentObstaclesVector.begin() + i;
                m_currentObstaclesVector.erase(itr, itr + 1);
            }
        }
    }
}

void ObstacleManager::SpawnObstacles()
{
    // SPAWN OBSTACLES
    int obstaclesToSpawn = random(1,m_maxObstacles); // Generates a random number to spawn

    std::vector<int> laneArray = {0,1,2,3};

    for (int i = 0; i < obstaclesToSpawn; i++)
    {
        int laneIndex = random(0 , std::size(laneArray) - 1);

        std::string texturePath;
        int textureIndex = random(0, 2);
        switch (textureIndex)
        {
        case 0:
            texturePath = TPATH_OBSTACLE_ROCK1;
            break;
        case 1:
            texturePath = TPATH_OBSTACLE_ROCK2;
            break;
        case 2:
            texturePath = TPATH_OBSTACLE_ROCK3;
            break;
        default:
            break;
        }

        Obstacle* newObstacle = new Obstacle(m_renderer, texturePath, Vector2D(OFFSCREEN_SPAWN_XPOS , TOP_LANE_YPOS - (laneArray[laneIndex] * LANE_WIDTH)));

        // CHECK IF THE LANE INDEX IS THE LAST ELEMENT IN LANEARRAY.
        if (laneIndex != std::size(laneArray) - 1)
        {
            std::swap(laneArray[laneIndex], laneArray[std::size(laneArray) -1]);
        }
        laneArray.pop_back();
		
        m_currentObstaclesVector.push_back(newObstacle);
    }

    int freeLaneIndex = random(0, std::size(laneArray) - 1);
    m_freeSpawnLane = laneArray[freeLaneIndex];
}
