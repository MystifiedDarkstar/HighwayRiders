#include "PowerUp.h"

PowerUp::PowerUp(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer, imagePath, startPosition)
{

}

PowerUp::~PowerUp()
{

}

void PowerUp::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void PowerUp::Update(float deltaTime, SDL_Event e)
{

}
