#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	// INITIALISE RENDERER
	m_renderer = renderer;

	// LOAD TEXTURE
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load GameObject texture!" << std::endl;
	}
	
	// SET POSITION
	m_position = startPosition;

	// SET ORIGIN
	m_Origin = new Vector2D((m_texture->GetWidth() / 2) , (m_texture->GetHeight() / 2));
	
	// SET SIZE OF COLLISION
	m_collisionRadius = ((m_texture->GetWidth() / 2) + (m_texture->GetHeight() / 2));
}

GameObject::~GameObject()
{
	m_renderer = nullptr;

	m_Origin = nullptr;
}

void GameObject::Render()
{

	m_texture->Render(m_position , SDL_FLIP_NONE);
}

void GameObject::Update(float deltaTime, SDL_Event e)
{

}

void GameObject::SetPosition(Vector2D newPosition)
{
	m_position = newPosition;
}

Vector2D GameObject::GetPosition()
{
	return m_position;
}
float GameObject::GetCollisionRadius()
{
	return m_collisionRadius;
}