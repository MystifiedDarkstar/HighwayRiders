#pragma once
#ifndef _TREEGAMEOBJECT_H
#define _TREEGAMEOBJECT_H

#include "GameObject.h"

class Background : public GameObject
{
public:
	Background(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Background();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

};

#endif // !_TREEGAMEOBJECT_H

