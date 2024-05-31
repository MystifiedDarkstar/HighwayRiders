#include "CarCustomisationScreen.h"
#include "Camera.h"

CarCustomisationScreen::CarCustomisationScreen(SDL_Renderer* renderer) : GameScreen(renderer)
{
    Camera::GetInstance()->ResetCamera();
    SetUpLevel();
}

CarCustomisationScreen::~CarCustomisationScreen()
{

}

void CarCustomisationScreen::Render()
{
    m_background->Render();

	if(m_selectedColour == 0)
		m_redValueText->SetColour(SDL_Color{ 255,150,0,255 }); // orange
	else
		m_redValueText->SetColour(SDL_Color{ 0,0,0,255 }); // black
    m_redValueText->RenderAt(std::to_string(SaveGame::Instance().ReturnPlayerColour().r), 157, 255, false);

	if (m_selectedColour == 1)
		m_greenValueText->SetColour(SDL_Color{ 255,150,0,255 }); // orange
	else
		m_greenValueText->SetColour(SDL_Color{ 0, 0, 0, 255 });
    m_greenValueText->RenderAt(std::to_string(SaveGame::Instance().ReturnPlayerColour().g), 257, 255, false);

	if (m_selectedColour == 2)
		m_blueValueText->SetColour(SDL_Color{ 255,150,0,255 }); // orange
	else
		m_blueValueText->SetColour(SDL_Color{ 0, 0, 0, 255 });
    m_blueValueText->RenderAt(std::to_string(SaveGame::Instance().ReturnPlayerColour().b), 357, 255, false);

    m_previewCar->SetColour(m_previewCarColor);
    m_previewCar->Render(Vector2D(455,175),SDL_FLIP_NONE);

}


void CarCustomisationScreen::Update(float deltaTime, SDL_Event e)
{
	// POLL INPUT
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_upKeyPressed = false;
			m_inputTimer = 0;
			break;
		case SDLK_DOWN:
			m_downKeyPressed = false;
			m_inputTimer = 0;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_upKeyPressed = true;
			break;
		case SDLK_DOWN:
			m_downKeyPressed = true;
			break;
		case SDLK_LEFT:
			if (m_selectedColour > 0)
				MoveLeftColour();
			break;
		case SDLK_RIGHT:
			if (m_selectedColour < 2)
				MoveRightColour();
			break;
		default:
			break;
		}
		break;
	case SDL_JOYBUTTONUP:
		switch (e.jbutton.button)
		{
		case 13:
			//UP
			m_upKeyPressed = false;
			break;
		case 16:
			// DOWN
			m_downKeyPressed = false;
			break;
		default: break;
		}
		break;
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 13:
			//UP
			m_upKeyPressed = true;
			break;
		case 14:
			if (m_selectedColour > 0)
				MoveLeftColour();
			break;
		case 15:
			if (m_selectedColour < 2)
				MoveRightColour();
			break;
		case 16:
			// DOWN
			m_downKeyPressed = true;
			break;
		default: break;
		}
		break;
	default:
		break;
	}

	if (m_upKeyPressed || m_downKeyPressed)
	{
		m_inputTimer -= deltaTime;
	}

	if (m_upKeyPressed && m_inputTimer <= 0)
	{
		IncreaseColourCount();
		m_inputTimer = 0.025f;
	}

	else if (m_downKeyPressed && m_inputTimer <= 0)
	{
		DecreaseColourCount();
		m_inputTimer = 0.025f;
	}
}

bool CarCustomisationScreen::SetUpLevel()
{
    m_background = new Background(m_renderer,TPATH_BACKGROUND_CUSTOMISATION, Vector2D(0,0));

    m_redValueText = new GUIText(m_renderer, TTFPATH_FRESHMAN, 30);
    m_blueValueText = new GUIText(m_renderer, TTFPATH_FRESHMAN, 30);
    m_greenValueText = new GUIText(m_renderer, TTFPATH_FRESHMAN, 30);

    m_previewCar = new Texture2D(m_renderer);
    if (!m_previewCar->LoadFromFile(TPATH_PREVIEWCAR))
        std::cout << "Failed to load texture. Path: " << TPATH_PREVIEWCAR << std::endl;

	m_previewCarColor = SaveGame::Instance().ReturnPlayerColour();

    return true;
}

void CarCustomisationScreen::IncreaseColourCount()
{
	switch (m_selectedColour)
	{
	case 0:
		if (m_previewCarColor.r < 255)
		{
			m_previewCarColor.r++;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	case 1:
		if (m_previewCarColor.g < 255) {
			m_previewCarColor.g++;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	case 2:
		if (m_previewCarColor.b < 255)
		{
			m_previewCarColor.b++;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	default:
		break;
	}
}

void CarCustomisationScreen::DecreaseColourCount()
{
	switch (m_selectedColour)
	{
	case 0:
		if (m_previewCarColor.r > 0)
		{
			m_previewCarColor.r--;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	case 1:
		if (m_previewCarColor.g > 0)
		{
			m_previewCarColor.g--;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	case 2:
		if (m_previewCarColor.b > 0)
		{
			m_previewCarColor.b--;
			SaveGame::Instance().SetPlayerColour(m_previewCarColor);
		}
		break;
	default:
		break;
	}
}

void CarCustomisationScreen::MoveLeftColour()
{
	m_selectedColour--;
}

void CarCustomisationScreen::MoveRightColour()
{
	m_selectedColour++;
}
