#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer,imagePath,startPosition)
{
    
}

Coin::~Coin()
{
    
}

void Coin::Render()
{
    m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Coin::Update(float deltaTime, SDL_Event e)
{
    
}
