#pragma once
#ifndef _OBSTACLEMANAGER_H
#define _OBSTACLEMANAGER_H

#include "SDL.h"
#include "Obstacle.h"
#include "Constants.h"
#include "Level1Globals.h"
#include <vector>
#include "PlayerCharacter.h"

class ObstacleManager
{
public:
    ObstacleManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player);
    ~ObstacleManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    inline int ReturnFreeSpawnLane() { return m_freeSpawnLane; }
    inline void SetMaxObstacles(int amt) { m_maxObstacles = amt; }
    inline void SetMinObstacles(int amt) { m_minObstacles = amt; }
    
    void SpawnObstacles();

private:
    SDL_Renderer* m_renderer = nullptr;
    Level1Globals* m_lvl1Globals = nullptr;
    PlayerCharacter* m_player = nullptr;

    int m_maxObstacles = 2;
    int m_minObstacles = 1;

    int m_freeSpawnLane = 0;

    std::vector<Obstacle*> m_currentObstaclesVector;
};

#endif