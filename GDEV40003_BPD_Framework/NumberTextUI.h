#pragma once
#ifndef _NUMNERTEXTUI_H
#define _NUMBERTEXTUI_H

#include "SDL.h"
#include <iostream>
#include <vector>

#include "Texture2D.h"

class NumberTextUI
{
public:
    NumberTextUI(SDL_Renderer* renderer);
    ~NumberTextUI();    

    void SetUpText(std::string text, int size);
    void LoadNumberTextInfo(float time);
    
    void Update(float deltaTime, SDL_Event e);
    void Render(Vector2D renderStartPos);
    
private:
    SDL_Renderer* m_renderer;
    std::vector<Texture2D*> m_textTextures;
    Texture2D* m_timeBackground;
    
    static std::string m_TexturePaths [];

    float m_lastTextUpdate;
    void UpdateText(std::string text, int size);
};

#endif