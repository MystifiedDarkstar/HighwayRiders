#pragma once

#ifndef _GUITEXT_H
#define _GUITEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class GUIText
{
public:
	GUIText(SDL_Renderer* renderer,const std::string fontPath, unsigned int fontSize);
	~GUIText();

	
	void RenderAt(const std::string text, int x , int y, bool isOutlined);
	void SetColour(SDL_Color color);

protected:
	SDL_Texture* m_texture = nullptr;
	SDL_Texture* m_textureOutline = nullptr;
	TTF_Font* m_font = nullptr;
	TTF_Font* m_fontOutline = nullptr;
	SDL_Color m_color {255,255,255,255};
	SDL_Renderer* m_renderer = nullptr;

private:
	void Destroy();

	static bool TTFHasInit;
	static bool InitTTF();

	bool LoadFont(const std::string fontPath, unsigned int fontSize);

	bool m_HasErrorEncountered = false;
};

#endif // !_GUITEXT_H
