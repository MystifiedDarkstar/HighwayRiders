#include "GUIText.h"

GUIText::GUIText(SDL_Renderer* renderer, const std::string fontPath, unsigned int fontSize)
{
	m_renderer = renderer;

	if (!InitTTF())
	{
		std::cerr << "Failed to initialise SDL_TTF; Error : " << TTF_GetError() << std::endl;
		m_HasErrorEncountered = true;
		return;
	}

	LoadFont(fontPath, fontSize);
}

GUIText::~GUIText()
{
	Destroy();
}

bool GUIText::LoadFont(const std::string fontPath, unsigned int fontSize)
{
	// TTF has been initialised
	m_font = TTF_OpenFont(fontPath.c_str(), fontSize);

	m_fontOutline = TTF_OpenFont(fontPath.c_str(), fontSize);
	TTF_SetFontOutline(m_fontOutline , 1);

	if (!m_font)
	{
		// No font has been loaded, send error
		std::cerr << "Failed to load TTF_FONT from path. Path : " << fontPath << "; Error : " << TTF_GetError() << std::endl;
		m_HasErrorEncountered = true;
		return false;
	}
	if (!m_fontOutline)
	{
		// No font has been loaded, send error
		std::cerr << "Failed to load TTF_FONT from path. Path : " << fontPath << "; Error : " << TTF_GetError() << std::endl;
		m_HasErrorEncountered = true;
		return false;
	}
	return true;
}

void GUIText::RenderAt(const std::string text, int x, int y, bool isOutlined)
{
	// Errors? Exit Render
	if (m_HasErrorEncountered)
		return;

	// Destroy Texture
	if (m_texture != nullptr)
		SDL_DestroyTexture(m_texture);
	//DESTROY OUTLINE TEXT
	if (m_textureOutline != nullptr)
		SDL_DestroyTexture(m_textureOutline);

	// Size the text
	int w, h;
	TTF_SizeText(m_font, text.c_str(), &w, &h);
	
	// Load surf and text
	SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str(), m_color);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	SDL_FreeSurface(surf);

	// get render rect and render with it
	SDL_Rect renderRect{ x, y, w, h };
	SDL_RenderCopy(m_renderer, m_texture, NULL, &renderRect);

	if (isOutlined)
	{
		int wOutline, hOutline;

		TTF_SizeText(m_fontOutline, text.c_str(), &wOutline, &hOutline);

		SDL_Surface* surf1 = TTF_RenderText_Blended(m_fontOutline, text.c_str(), SDL_Color{ 0,0,0,200 });
		m_textureOutline = SDL_CreateTextureFromSurface(m_renderer, surf1);
		SDL_FreeSurface(surf1);

		SDL_Rect renderRectOutline{ x, y, wOutline, hOutline };
		SDL_RenderCopy(m_renderer, m_textureOutline, NULL, &renderRectOutline);
	}
}

void GUIText::SetColour(SDL_Color color)
{
	m_color = color;
}

void GUIText::Destroy()
{
	TTF_CloseFont(m_font);
	TTF_CloseFont(m_fontOutline);
}

bool GUIText::InitTTF()
{
	// Already Intited
	if (TTFHasInit)
		return true;

	//Init TTF, return error if not inited correctly
	return (TTF_Init() >= 0);
}

bool GUIText::TTFHasInit = false;