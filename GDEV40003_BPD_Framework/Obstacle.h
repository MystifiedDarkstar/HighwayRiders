#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
    Obstacle(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
    ~Obstacle();

    virtual void Render() override;
    virtual void Update(float deltaTime , SDL_Event e);
};
