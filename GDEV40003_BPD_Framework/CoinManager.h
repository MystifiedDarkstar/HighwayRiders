#pragma once
#ifndef _COINMANAGER_H
#define _COINMANAGER_H

#include <vector>

#include "SDL.h"
#include "Coin.h"
#include "GUIText.h"
#include "Commons.h"
#include <fstream>
#include <iostream>
#include "Level1Globals.h"
#include "ScoreManager.h"
#include "PlayerCharacter.h"

class CoinManager
{
public:
    CoinManager(SDL_Renderer* renderer, Level1Globals* lvl1Globals, PlayerCharacter* player, ScoreManager* scoreMan);
    ~CoinManager();

    void Render();
    void Update(float deltaTime, SDL_Event e);

    void SpawnCoin(int spawnLane);

private:
    void IncreaseCoinCount();
    void RemoveCoinObject(int index);

    void SetUpManager();

private:
    SDL_Renderer* m_renderer = nullptr;
    Level1Globals* m_lvl1Globals = nullptr;
    PlayerCharacter* m_player = nullptr;
    ScoreManager* m_scoreManager = nullptr;
    
    std::vector<Coin*> m_currentCoinsVector;

    int m_coinCount = 0;
    GUIText* m_coinCountText = nullptr;
};

#endif