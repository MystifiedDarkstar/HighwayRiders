#include "GameTitleScreen.h"
#include "Camera.h"
#include "MathFunctions.h"
#include <iostream>

GameTitleScreen::GameTitleScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
	Camera::GetInstance()->ResetCamera();
	SetUpLevel();
}
GameTitleScreen::~GameTitleScreen()
{
	delete m_background;
	m_background = nullptr;

	delete m_menuText;
	m_menuText = nullptr;

	delete m_timerText;
	m_timerText = nullptr;

	delete m_scoreText;
	m_scoreText = nullptr;
}
void GameTitleScreen::Update(float deltaTime, SDL_Event e)
{
	m_menuTextAlpha = static_cast<int>(std::abs(std::sin(m_menuTextAlphaFloat) * 255.0f));
	m_menuTextAlphaFloat += 0.025;
}
void GameTitleScreen::Render()
{
	// DRAW THE BACKGROUND
	m_background->Render();

	// RENDER TEXT 
	m_timerText->SetColour(SDL_Color{255,150,0,255}); // ORANGE
	m_timerText->RenderAt("HIGHTIME : " + ConvertTimeToString(m_levelTimeAllTime), 20, 70 , true);

	m_scoreText->SetColour(SDL_Color{ 255,150,0,255 }); // ORANGE
	m_scoreText->RenderAt("HIGHSCORE : " + std::to_string(m_scoreAllTime), 20, 100 , true);

	m_menuText->SetOpacity(m_menuTextAlpha);
	m_menuText->Render(Vector2D(0,0), SDL_FLIP_NONE, 0);
}

bool GameTitleScreen::SetUpLevel()
{
	// LOAD TEXTURE
	m_background = new Background (m_renderer, TPATH_BACKGROUND_TITLE, Vector2D(0, 0));

	m_menuText = new Texture2D(m_renderer);
	if (!m_menuText->LoadFromFile(TPATH_BACKGROUND_TITLETEXT))
		std::cout << "ERROR: Failed to load texture. Path: " << TPATH_BACKGROUND_TITLETEXT << std::endl;

	// SETUP GUI TEXT
	m_timerText = new GUIText (m_renderer, TTFPATH_ROBOTO, 28);
	m_scoreText = new GUIText(m_renderer, TTFPATH_ROBOTO, 28);

	m_levelTimeAllTime = SaveGame::Instance().GetLevelAllTime();
	m_scoreAllTime = SaveGame::Instance().GetHighScore();

	// SET THE TARGET OF THE CAMERA TO THE BACKGROUND ORIGIN (Center of the screen)
	Camera::GetInstance()->SetTarget(m_background->GetOrigin());

	return true;
}
