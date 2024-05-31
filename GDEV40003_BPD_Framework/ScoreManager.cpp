#include "ScoreManager.h"

ScoreManager::ScoreManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals)
{
	m_renderer = renderer;
    m_lvl1Globals = lvl1Globals;
	SetUpManager();
}

ScoreManager::~ScoreManager()
{
    delete m_scoreText;
    m_scoreText = nullptr;
}

void ScoreManager::SetUpManager()
{
	m_scoreText = new GUIText (m_renderer,TTFPATH_FRESHMAN , 26);
}

void ScoreManager::Update(float deltaTime, SDL_Event e)
{
    if (m_lvl1Globals->g_isGameActive)
    {
        m_timer += deltaTime;

        if (m_timer >= 1.0f)
        {
            m_score += std::floor(1.5f * m_lvl1Globals->g_scoreMultiplier);
            m_timer = 0;
        }
    }
    else if (!m_lvl1Globals->g_isStartGame && !m_lvl1Globals->g_isGameActive)
    {
        CheckHighScore();
    }
}

void ScoreManager::Render()
{
	m_scoreText->SetColour(SDL_Color{0,0,0,255});
	m_scoreText->RenderAt("Score: " + std::to_string(m_score), 600, 16, false);
}

void ScoreManager::CheckHighScore()
{
    SaveGame::Instance().SetLastGameScore(m_score);

    if (m_score > SaveGame::Instance().GetHighScore())
    {
        SaveGame::Instance().SetHighScore(m_score);
    }
}

void ScoreManager::AddCoin()
{
    m_totalCoinCount++;
    m_score += (1 * 3.0f) * m_lvl1Globals->g_scoreMultiplier;
}

void ScoreManager::AddLevelTime(float deltaTime)
{
    m_score += (deltaTime * 1.5f) * m_lvl1Globals->g_scoreMultiplier;
}

