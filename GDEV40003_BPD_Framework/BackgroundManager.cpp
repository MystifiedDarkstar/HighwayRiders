#include "BackgroundManager.h"
#include "Camera.h"

BackgroundManager::BackgroundManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals)
{
    m_renderer = renderer;
    m_lvl1Globals = lvl1Globals;

    SetUpBackgrounds();
}

BackgroundManager::~BackgroundManager()
{
    // DELETE BACKGROUNDS FROM MEMORY.
    m_currentBackgroundsVector.clear();
    m_currentBackgroundsVector.shrink_to_fit();
}

void BackgroundManager::Render()
{
    // DRAW THE BACKGROUNDS
    for (int i = 0; i < m_currentBackgroundsVector.size(); i++)
    {
        m_currentBackgroundsVector[i]->Render();
    }
}

void BackgroundManager::Update(float deltaTime, SDL_Event e)
{
    int camXPos = Camera::GetInstance()->GetViewBox().x;

    // CHECK IF BACKGROUND IS OUT OF CAMERA VIEW, IF SO DELETE BACKGROUND AND RECREATE AHEAD OF PLAYER
    if (m_currentBackgroundsVector.size() > 0 && camXPos - m_currentBackgroundsVector[0]->GetPosition().x > 1800)
    {
        UpdateBackgroundPosition(0,Vector2D(m_currentBackgroundsVector[1]->GetPosition().x + 1600, 0));
        std::iter_swap(m_currentBackgroundsVector.begin(), m_currentBackgroundsVector.begin() + 1);
    }

    if (m_lvl1Globals->g_isGameActive)
    {
        for (int i = 0; i < m_currentBackgroundsVector.size(); i++)
        {
            Vector2D position = m_currentBackgroundsVector[i]->GetPosition();
            position.x -= deltaTime * (SCROLL_SPEED * m_lvl1Globals->g_scrollSpeedMultiplier);
            UpdateBackgroundPosition(i, position);  
        }
    }
}

void BackgroundManager::UpdateBackgroundPosition(int bgrdIndex, Vector2D newPos)
{
    m_currentBackgroundsVector[bgrdIndex]->SetPosition(newPos);
}

void BackgroundManager::SetUpBackgrounds()
{
    m_currentBackgroundsVector.resize(BACKGROUND_COUNT);
    // LOAD BACKGROUND TEXTURE
    for (int i = 0; i < BACKGROUND_COUNT; i++)
    {
        m_currentBackgroundsVector[i] =  new Background (m_renderer, TPATH_BACKGROUND_LEVEL1, Vector2D(i * BACKGROUND_WIDTH, 0));
    }
}



