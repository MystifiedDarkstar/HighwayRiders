#include "Obstacle.h"

Obstacle::Obstacle(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer,imagePath,startPosition)
{
    
}
Obstacle::~Obstacle()
{
    
}
void Obstacle::Render()
{
    m_texture->Render(m_position, SDL_FLIP_NONE);
}
void Obstacle::Update(float deltaTime, SDL_Event e)
{
    
}




