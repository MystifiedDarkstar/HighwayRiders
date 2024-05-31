#include "GameOverScreen.h"
#include "Texture2D.h"
#include <iostream>
#include "Camera.h"
#include "MathFunctions.h"
#include "SaveGame.h"

GameOverScreen::GameOverScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
    Camera::GetInstance()->ResetCamera();
    SetUpLevel();
}
GameOverScreen::~GameOverScreen()
{
    delete m_menuBackground;
    m_menuBackground = nullptr;

    delete m_menuText;
    m_menuText = nullptr;

    delete m_timerText;
    m_timerText = nullptr;

    delete m_scoreText;
    m_scoreText = nullptr;
}

void GameOverScreen::Update(float deltaTime, SDL_Event e)
{
    m_menuTextAlpha = static_cast<int>(std::abs(std::sin(m_menuTextAlphaFloat) * 255.0f));
    m_menuTextAlphaFloat += 0.015;
}

void GameOverScreen::Render()
{
    // DRAW THE BACKGROUND
    m_menuBackground->Render();

    m_menuText->SetOpacity(m_menuTextAlpha);
    m_menuText->Render(Vector2D(0,0), SDL_FLIP_NONE);

    // RENDER TEXT 
    m_timerText->SetColour(SDL_Color{ 255,150,0,255 }); // ORANGE
    m_timerText->RenderAt("YOUR TIME : " + ConvertTimeToString(SaveGame::Instance().GetLastGameLevelTime()), 20, 70, true);

    m_scoreText->SetColour(SDL_Color{ 255,150,0,255 }); // ORANGE
    m_scoreText->RenderAt("YOU SCORED : " + std::to_string(SaveGame::Instance().GetLastGameScore()), 20, 100, true);
}
bool GameOverScreen::SetUpLevel()
{
    // LOAD TEXTURE
    m_menuBackground = new Background (m_renderer, TPATH_BACKGROUND_GAMEOVER, Vector2D(0, 0));

    m_menuText = new Texture2D(m_renderer);
    if (!m_menuText->LoadFromFile(TPATH_BACKGROUND_GAMEOVERMENUTEXT))
        std::cout << "ERROR: Failed to load texture. Path: " << TPATH_BACKGROUND_GAMEOVERMENUTEXT << std::endl;

    // SETUP GUI TEXT
    m_timerText = new GUIText(m_renderer, TTFPATH_ROBOTO, 28);
    m_scoreText = new GUIText(m_renderer, TTFPATH_ROBOTO, 28);

    m_levelTimeAllTime = SaveGame::Instance().GetLevelAllTime();
    m_scoreAllTime = SaveGame::Instance().GetHighScore();

    Camera::GetInstance()->SetTarget(m_menuBackground->GetOrigin());

    return true;
}
