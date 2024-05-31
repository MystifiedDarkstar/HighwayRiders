#include "PlayerCharacter.h"

#include "GameScreenLevel1.h"
#include "Texture2D.h"

PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, Level1Globals* lvl1Globals, Colour carColour) : GameObject(renderer , imagePath, startPosition)
{
	m_lvl1Globals = lvl1Globals;
	m_carColour = carColour;
}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Render()
{
	m_texture->SetColour(m_carColour);
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void PlayerCharacter::Update(float deltaTime , SDL_Event e)
{
	if (m_lvl1Globals->g_isGameActive)
	{
	// PLAYER MOVEMENT
		if (m_upKeyPressed || m_downKeyPressed)
		{
			m_inputTimer -= deltaTime;
		}

		// PLAYER DODGE
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				m_upKeyPressed = false;
				m_inputTimer = 0;
				break;
			case SDLK_w:
				m_upKeyPressed = false;
				m_inputTimer = 0;
				break;
			case SDLK_DOWN:
				m_downKeyPressed = false;
				m_inputTimer = 0;
				break;
			case SDLK_s:
				m_downKeyPressed = false;
				m_inputTimer = 0;
				break;
			default:
				break;
			}
		}

		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				m_upKeyPressed = true;
				break;
			case SDLK_w:
				m_upKeyPressed = true;
				break;
			case SDLK_DOWN:
				m_downKeyPressed = true;
				break;
			case SDLK_s:
				m_downKeyPressed = true;
				break;
			default:
				break;
			}
		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			switch (e.jbutton.button)
			{
			case 13:
				//UP
				m_upKeyPressed = true;
				break;

			case 16: 
				// DOWN
				m_downKeyPressed = true;
				break;

			default: break;
			}
		}

		else if (e.type == SDL_JOYBUTTONUP)
		{
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
		}

		if (m_upKeyPressed && m_currentPlayerTrack < LEVEL1_LANES && m_inputTimer <= 0)
		{
			MoveUpTrack(deltaTime); // move the player to the above track
			m_currentPlayerTrack++; // increment the current track the player is on.
			m_inputTimer = 0.1f;
		}

		else if (m_downKeyPressed && m_currentPlayerTrack > 0 && m_inputTimer <= 0)
		{
			MoveDownTrack(deltaTime); // move the player to the above track
			m_currentPlayerTrack--; // increment the current track the player is on.
			m_inputTimer = 0.15f;
		}

	// UPDATE PLAYER ORIGIN (Is for camera target, but player dosent move)
		m_Origin->x = m_position.x + (m_texture->GetWidth() / 2);
		m_Origin->y = m_position.y + (m_texture->GetHeight() / 2);
	}
}

void PlayerCharacter::MoveDownTrack(float deltaTim)
{
	m_position.y += 64.0f;
}

void PlayerCharacter::MoveUpTrack(float deltaTime)
{
	m_position.y -= 64.0f;
}



