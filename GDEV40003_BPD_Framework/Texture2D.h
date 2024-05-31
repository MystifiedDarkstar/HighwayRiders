#pragma once

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();
	
	bool LoadFromFile(std::string path);

	void Free();

	void Render(Vector2D new_position , SDL_RendererFlip flip, double angle = 0.0);

	void SetColour(Colour colour);
	void SetOpacity(Uint8 alpha);

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_width;
	int m_height;
};

#endif // _TEXTURE2D_H

