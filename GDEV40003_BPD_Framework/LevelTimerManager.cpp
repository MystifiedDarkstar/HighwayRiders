#include "LevelTimerManager.h"
#include "Camera.h"
#include "MathFunctions.h"


LevelTimerManager::LevelTimerManager(SDL_Renderer* renderer,Level1Globals* lvl1Globals, ScoreManager* scoreMan)
{
    m_renderer = renderer;
    m_lvl1Globals = lvl1Globals;

    m_scoreManager = scoreMan;

    m_levelTimer = 0;

    SetUpTimerManager();
}

LevelTimerManager::~LevelTimerManager()
{
    delete m_timerText;
    m_timerText = nullptr;
}

void LevelTimerManager::Update(float deltaTime, SDL_Event e)
{
    if (m_lvl1Globals->g_isGameActive)
    {
        m_levelTimer += deltaTime;
        
        if (m_levelTimer == 20.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 1;
        }
        else if (m_levelTimer == 40.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 2;
        }
        else if (m_levelTimer == 60.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 3;
        }
        else if (m_levelTimer == 80.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 4;
        }
        else if (m_levelTimer == 100.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 5;
        }
        else if (m_levelTimer == 120.0f)
        {
            m_lvl1Globals->g_gameDifficulty = 6;
        }
    }
    // Triggers if game has been running and is now finished.
    else if (!m_lvl1Globals->g_isStartGame && !m_lvl1Globals->g_isGameActive)
    {
        CheckLevelHighScore();
    }
}

void LevelTimerManager::Render()
{
    m_timerText->SetColour(SDL_Color{ 0, 0, 0, 255 });
    m_timerText->RenderAt("Time: " + ConvertTimeToString(m_levelTimer), 20, 16, false);
}

void LevelTimerManager::CheckLevelHighScore()
{
    SaveGame::Instance().SetLastGameLevelTime(std::floor(m_levelTimer));

    if (std::floor(m_levelTimer) > SaveGame::Instance().GetLevelAllTime())
    {
        SaveGame::Instance().SetLevelAllTime(std::floor(m_levelTimer));
    }
}

void LevelTimerManager::SetUpTimerManager()
{
    m_timerText = new GUIText(m_renderer, TTFPATH_FRESHMAN, 26);
}