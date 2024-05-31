#pragma once
#ifndef _GAMEOVERSCREEN_H
#define _GAMEOVERSCREEN_H

#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Background.h"
#include "GUIText.h"

class Texture2D;

class GameOverScreen : GameScreen
{
public:
    GameOverScreen(SDL_Renderer* renderer);
    ~GameOverScreen() override;

    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;

private:
    bool SetUpLevel();

private:
    Background* m_menuBackground = nullptr;
    Texture2D* m_menuText = nullptr;

    Uint8 m_menuTextAlpha = 255;
    float m_menuTextAlphaFloat = 255;

    GUIText* m_timerText = nullptr;
    GUIText* m_scoreText = nullptr;

    int m_levelTimeAllTime = 0;
    int m_scoreAllTime = 0;
};
#endif // !_GAMEOVERSCREEN_H