#include "CoinManager.h"
#include "MathFunctions.h"
#include "Camera.h"
#include "AudioManager.h"
#include "Collisions.h"

CoinManager::CoinManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player, ScoreManager* scoreMan)
{
    m_renderer = renderer;
    m_lvl1Globals = lvl1Globals;
    m_player = player;
    m_scoreManager = scoreMan;

    SetUpManager();
}

CoinManager::~CoinManager()
{
    for (int i = 0; i < m_currentCoinsVector.size(); i++)
    {
        delete m_currentCoinsVector[i];
    }
    m_currentCoinsVector.clear();
    m_currentCoinsVector.shrink_to_fit();

    delete m_coinCountText;
    m_coinCountText = nullptr;
}

void CoinManager::Render()
{
    for (int i = 0; i < m_currentCoinsVector.size(); i++)
    {
        m_currentCoinsVector[i]->Render();
    }

    m_coinCountText->SetColour(SDL_Color{ 0, 0, 0, 255 }); // black
    m_coinCountText->RenderAt("Coins: " + std::to_string(m_coinCount), 20, 46, false);
}

void CoinManager::Update(float deltaTime, SDL_Event e)
{
    if (m_lvl1Globals->g_isGameActive)
    {        
        // CHECK PLAYER / COIN COLLISION
        for (int i = 0; i < m_currentCoinsVector.size(); i++)
        {
            if (Collisions::Instance()->Box(m_player->GetCollisionBox(), m_currentCoinsVector[i]->GetCollisionBox()))
            {
                RemoveCoinObject(i);
                AudioManager::Instance().PlayCoinCollect();
            }
        }

        // SCROLL COINS
        for (int i = 0; i < m_currentCoinsVector.size(); i++)
        {
            Vector2D position = m_currentCoinsVector[i]->GetPosition();
            position.x -= deltaTime * (SCROLL_SPEED * m_lvl1Globals->g_scrollSpeedMultiplier);
            m_currentCoinsVector[i]->SetPosition(position);
        }

        // CHECK IF COINS OUT OF CAMERA VIEW AND DELETE
        int camXPos = Camera::GetInstance()->GetViewBox().x;

        for (int i = 0; i < m_currentCoinsVector.size(); i++)
        {
            if (camXPos - m_currentCoinsVector[i]->GetPosition().x > 200)
            {
                delete m_currentCoinsVector[i];
                auto itr = m_currentCoinsVector.begin() + i;
                m_currentCoinsVector.erase(itr, itr + 1);
            }
        }
    }
}

void CoinManager::SetUpManager()
{
    m_coinCountText = new GUIText(m_renderer, TTFPATH_FRESHMAN, 26);
}

void CoinManager::SpawnCoin(int spawnLane)
{
    Coin* newObstacle = new Coin (m_renderer, TPATH_COLLECTABLE_COIN1, Vector2D(OFFSCREEN_SPAWN_XPOS , TOP_LANE_YPOS - (spawnLane * LANE_WIDTH)));
    m_currentCoinsVector.push_back(newObstacle);
}

void CoinManager::IncreaseCoinCount()
{
    m_coinCount++;
}

void CoinManager::RemoveCoinObject(int index)
{
    delete m_currentCoinsVector[index];
    auto itr = m_currentCoinsVector.begin() + index;
    m_currentCoinsVector.erase(itr, itr + 1);

    IncreaseCoinCount();
    m_scoreManager->AddCoin();
}


