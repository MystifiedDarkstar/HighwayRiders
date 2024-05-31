#pragma once
#ifndef _LEVELTIMERMANAGER_H
#define _LEVELTIMERMANAGER_H

#include "SDL.h"
#include <fstream>
#include "GUIText.h"
#include "Texture2D.h"
#include "Level1Globals.h"
#include "ScoreManager.h"
#include "SaveGame.h"

#define TIMERSTARTPOSITIONX 320

class LevelTimerManager
{
public:
    LevelTimerManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals, ScoreManager* scoreMan);
    ~LevelTimerManager();
 
    void Update(float deltaTime, SDL_Event e);
    void Render();

    inline float GetLevelTimer() { return m_levelTimer; }
    
private:
    void SetUpTimerManager();
    void CheckLevelHighScore();

private:

    SDL_Renderer* m_renderer = nullptr;
    Level1Globals* m_lvl1Globals = nullptr;
    ScoreManager* m_scoreManager = nullptr;

    GUIText* m_timerText = nullptr;
    
    float m_levelTimer;
};

#endif