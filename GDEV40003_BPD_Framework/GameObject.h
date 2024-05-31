#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

class Texture2D;

class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	virtual ~GameObject();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	inline Vector2D* GetOrigin() {return m_Origin;}
	
	float GetCollisionRadius();	
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

protected:
	SDL_Renderer* m_renderer = nullptr;
	Vector2D m_position;
	Texture2D* m_texture = nullptr;
	Vector2D* m_Origin = nullptr;

	float m_collisionRadius;
};


#endif // !_GAMEOBJECT_H
