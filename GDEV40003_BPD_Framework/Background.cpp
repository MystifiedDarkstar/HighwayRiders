#include "Background.h"
#include "Texture2D.h"

Background::Background(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer, imagePath, startPosition)
{

}

Background::~Background()
{

}

void Background::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Background::Update(float deltaTime, SDL_Event e)
{
	
}