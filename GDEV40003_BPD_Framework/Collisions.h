#pragma once
#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "Commons.h"
#include "GameObject.h"

class PlayerCharacter;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(GameObject* a, GameObject* b);
	bool Box(Rect2D rect1, Rect2D rect2);
private:
	Collisions();

	static Collisions* m_instance;
};

#endif // !_COLLISIONS_H
