#pragma once
#ifndef _POWERUP_H
#define _POWERUP_H

#include "SDL.h"
#include "GameObject.h"
#include "Commons.h"

class PowerUp : public GameObject
{
public:
    PowerUp(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
    ~PowerUp();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    inline PowerUps ReturnPowerUPType() { return powerUpTag; }
    inline void SetPowerUPType(PowerUps newPowerType) { powerUpTag = newPowerType; }

private:
    PowerUps powerUpTag;
};

#endif
