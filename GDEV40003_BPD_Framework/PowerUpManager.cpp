#include "PowerUpManager.h"
#include "Camera.h"
#include "MathFunctions.h"
#include "Collisions.h"

PowerUpManager::PowerUpManager(SDL_Renderer* renderer, Level1Globals* level1Globals, PlayerCharacter* player)
{
    m_renderer = renderer;
    m_lvl1Globals = level1Globals;
    m_player = player;

    SetUpManager();
}

PowerUpManager::~PowerUpManager()
{
    for (int i = 0; i < m_currentPowerUpsVector.size(); i++)
    {
        delete m_currentPowerUpsVector[i];
    }
    m_currentPowerUpsVector.clear();
    m_currentPowerUpsVector.shrink_to_fit();
}

void PowerUpManager::Render()
{
    for (int i = 0; i < m_currentPowerUpsVector.size(); i++)
    {
        m_currentPowerUpsVector[i]->Render();
    }

    std::string typeInfo;
    switch (m_activePowerUPType)
    {
    case NONE:
        typeInfo = "";
        break;
    case SPEEDUP:
        typeInfo = "Speed Up";
        break;
    case SLOWDOWN:
        typeInfo = "Slow Down";
        break;
    case MULTIPLIERx2:
        typeInfo = "2X Score";
        break;
    case MULTIPLIERx5:
        typeInfo = "5X Score";
        break;
    default:
        break;
    }

    m_powerUpInfo->SetColour(SDL_Color{ 0,0,0,255 });
    m_powerUpInfo->RenderAt(typeInfo, 600, 46, false);
}

void PowerUpManager::Update(float deltaTime, SDL_Event e)
{
    if (m_lvl1Globals->g_isGameActive)
    {
        // CHECK COLLISION WITH PLAYER
        for (int i = 0; i < m_currentPowerUpsVector.size(); i++)
        {
            if (Collisions::Instance()->Box(m_player->GetCollisionBox(), m_currentPowerUpsVector[i]->GetCollisionBox()))
            {
                RemovePowerUpObject(i);
            }
        }

        // DECREMENT ACTIVE POWER UP TIMER
        if(m_isActivePowerUP)
            m_activePowerUPTimer -= deltaTime;

        // CHECK IF ACTIVE POWER UP TIMER IS LESS THAN 0
        if (m_activePowerUPTimer <= 0)
        {
            m_lvl1Globals->g_scoreMultiplier = 1.0f;
            m_lvl1Globals->g_scrollSpeedMultiplier = 1.0f;
            m_activePowerUPType = NONE;
            m_isActivePowerUP = false;
        }

        // SCROLL POWER UP OBJECTS
        for (int i = 0; i < m_currentPowerUpsVector.size(); i++)
        {
            Vector2D position = m_currentPowerUpsVector[i]->GetPosition();
            position.x -= deltaTime * (SCROLL_SPEED * m_lvl1Globals->g_scrollSpeedMultiplier);
            m_currentPowerUpsVector[i]->SetPosition(position);
        }

        // CHECK IF POWER UPS OUT OF CAMERA VIEW AND DELETE
        int camXPos = Camera::GetInstance()->GetViewBox().x;

        for (int i = 0; i < m_currentPowerUpsVector.size(); i++)
        {
            if (camXPos - m_currentPowerUpsVector[i]->GetPosition().x > 200)
            {
                delete m_currentPowerUpsVector[i];
                auto itr = m_currentPowerUpsVector.begin() + i;
                m_currentPowerUpsVector.erase(itr, itr + 1);
            }
        }
    }
}

void PowerUpManager::RemovePowerUpObject(int index)
{
    ExecutePowerUp(m_currentPowerUpsVector[index]->ReturnPowerUPType());
    delete m_currentPowerUpsVector[index];
    auto itr = m_currentPowerUpsVector.begin() + index;
    m_currentPowerUpsVector.erase(itr, itr + 1);
}

void PowerUpManager::SetUpManager()
{
    m_powerUpInfo = new GUIText(m_renderer, TTFPATH_FRESHMAN, 26);
}

void PowerUpManager::ExecutePowerUp(PowerUps powerUPType)
{
    switch (powerUPType)
    {
    case NONE:
        break;
    case SPEEDUP:
        m_lvl1Globals->g_scrollSpeedMultiplier = 1.5f;
        m_activePowerUPTimer = m_defaultPowerUpTimer;
        m_isActivePowerUP = true;
        m_activePowerUPType = SPEEDUP;
        break;
    case SLOWDOWN:
        m_lvl1Globals->g_scrollSpeedMultiplier = 0.5f;
        m_activePowerUPTimer = m_defaultPowerUpTimer;
        m_isActivePowerUP = true;
        m_activePowerUPType = SLOWDOWN;
        break;
    case MULTIPLIERx2:
        m_lvl1Globals->g_scoreMultiplier = 2.0f;
        m_activePowerUPTimer = m_defaultPowerUpTimer;
        m_isActivePowerUP = true;
        m_activePowerUPType = MULTIPLIERx2;
        break;
    case MULTIPLIERx5:
        m_lvl1Globals->g_scoreMultiplier = 5.0f;
        m_activePowerUPTimer = m_defaultPowerUpTimer;
        m_isActivePowerUP = true;
        m_activePowerUPType = MULTIPLIERx5;
        break;
    default:
        break;
    }
}

void PowerUpManager::SpawnPowerUp(int lane)
{
    PowerUp* newPowerUp = nullptr;

    int spawnLane = random(0,3);

    int powerUpType = random(0,3);
    switch (powerUpType)
    {
    case 0:
        newPowerUp = new PowerUp(m_renderer, TPATH_POWERUP_SPEEDUP, Vector2D(OFFSCREEN_SPAWN_XPOS, TOP_LANE_YPOS - (lane * LANE_WIDTH)));
        newPowerUp->SetPowerUPType(SPEEDUP);
        break;
    case 1:
        newPowerUp = new PowerUp(m_renderer, TPATH_POWERUP_SLOWDOWN, Vector2D(OFFSCREEN_SPAWN_XPOS, TOP_LANE_YPOS - (lane * LANE_WIDTH)));
        newPowerUp->SetPowerUPType(SLOWDOWN);
        break;
    case 2:
        newPowerUp = new PowerUp(m_renderer, TPATH_POWERUP_2XMULTIPLIER, Vector2D(OFFSCREEN_SPAWN_XPOS, TOP_LANE_YPOS - (lane * LANE_WIDTH)));
        newPowerUp->SetPowerUPType(MULTIPLIERx2);
        break;
    case 3:
        newPowerUp = new PowerUp(m_renderer, TPATH_POWERUP_5XMULTIPLIER, Vector2D(OFFSCREEN_SPAWN_XPOS, TOP_LANE_YPOS - (lane * LANE_WIDTH)));
        newPowerUp->SetPowerUPType(MULTIPLIERx5);
        break;
    default:
        break;
    }

    m_currentPowerUpsVector.push_back(newPowerUp);
}
