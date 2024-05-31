#pragma once
#ifndef _COIN_H
#define _COIN_H

#include "SDL.h"
#include "GameObject.h"
#include "Commons.h"

class Coin : public GameObject
{
public:
    Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
    ~Coin();

    void Render();
    void Update(float deltaTime, SDL_Event e);
};

#endif