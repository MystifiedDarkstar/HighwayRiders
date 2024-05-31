#include "Texture2D.h"
#include "SDL_image.h"
#include <iostream>
#include "Camera.h"

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
Texture2D::~Texture2D()
{
	// FREE UP MEMORY
	Free();
	m_renderer = nullptr;

}

bool Texture2D::LoadFromFile(std::string path)
{
	// REMOVE MEMORY USED FOR A PREVIOUS TETURE
	Free();

	//LOAD THE IMAGE
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//COLOUR KEY THE IMAGE TO BE TRANSPARENT
		SDL_SetColorKey(p_surface , SDL_TRUE, SDL_MapRGB(p_surface->format, 0XFF,0XFF,0XFF));

		// CREATE THE TEXTURE FROM THE PIXELS ON THE SURFACE
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			std::cout << "Unable to create texture from surface. EWrror: " << SDL_GetError() << std::endl;
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		SDL_FreeSurface(p_surface);
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl;
	}
	return m_texture != nullptr;
}
void Texture2D::Free()
{
	// CHECK IF TEXTURE EXISTS BEFORE REMOVING IT
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

		m_height = 0;
		m_width = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	Vector2D cam = Camera::GetInstance()->GetPosition();
	
	// SET WHERE TO RENDER THE TEXTURE
	SDL_Rect renderLocation = { new_position.x - cam.x, new_position.y, m_width, m_height };

	// RENDER TO SCREEN
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, angle, NULL, flip);

}

void Texture2D::SetColour(Colour colour)
{
	SDL_SetTextureColorMod(m_texture, colour.r, colour.g, colour.b);
}

void Texture2D::SetOpacity(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_texture, alpha);
}
