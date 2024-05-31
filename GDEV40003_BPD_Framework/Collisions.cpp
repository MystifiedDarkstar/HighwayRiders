#include "Collisions.h"
#include "PlayerCharacter.h"

// INITIALISE INSTANCE TO NULLPTR
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}
	return m_instance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.xPos + rect1.width > rect2.xPos &&
		rect1.xPos < rect2.xPos + rect2.width &&
		rect1.yPos + rect1.height > rect2.yPos &&
		rect1.yPos < rect2.yPos + rect2.height) 
	{
		return true;
	}
	return false;
}

bool Collisions::Circle(GameObject* a, GameObject* b)
{
	Vector2D vec = Vector2D((a->GetPosition().x - b->GetPosition().x), (a->GetPosition().y - b->GetPosition().y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance(a->GetCollisionRadius() + b->GetCollisionRadius());

	return distance < combined_distance;
}