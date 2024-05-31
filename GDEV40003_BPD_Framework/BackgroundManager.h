#pragma once
#ifndef _BACKGROUNDMANAGER_H
#define _BACKGROUNDMANAGER_H

#include <vector>

#include "SDL.h"
#include "Constants.h"
#include "Background.h"
#include "Level1Globals.h"
#include <iostream>
#include <algorithm>

class BackgroundManager
{
public:

    BackgroundManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals);
    ~BackgroundManager();
    
    void Render();
    void Update(float deltaTime, SDL_Event e);

    void SetUpBackgrounds();
    
private:
    void UpdateBackgroundPosition(int bgrdIndex, Vector2D newPos);

private:
    SDL_Renderer* m_renderer = nullptr;
    Level1Globals* m_lvl1Globals = nullptr;

    std::vector<Background*> m_currentBackgroundsVector;
    
};

#endif  