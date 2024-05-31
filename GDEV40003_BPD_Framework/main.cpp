#include "GameScreenManager.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDL_image.h"
#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include <Windows.h>

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;

GameScreenManager* game_screen_manager;

Uint32 g_old_time;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* argv[])
{
	if (InitSDL())
	{
		std::cout << "SDL Init" << std::endl;
		// INITIALISE THE SCREEN MANAGER
		game_screen_manager = new GameScreenManager(g_renderer , SCREEN_TITLE);
		
		TTF_Init();

		// SET THE OLD TIME
		g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{

			// CLEAR THE SCREEN
			SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(g_renderer);

			// CALL RENDER
			game_screen_manager->Render();

			// UPDATE THE SCREEN
			SDL_RenderPresent(g_renderer);

			quit = Update();
		}
	}
	
	
	CloseSDL();
	
	return 0;
}
bool Update()
{
	//event Handler
	SDL_Event e;

	// CREATE NEW TIME VARIABLE
	Uint32 new_time = SDL_GetTicks();

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//Click the 'X' to quit	
	case SDL_QUIT:
		return true;
		break;
	default:
		break;
	}
	// CALL SCREEN MANAGER UPDATE AND PASS TIME AND EVENT
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f , e);

	// SET OLD TIME TO NEW TIME
	g_old_time = new_time;

	return false;
}
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "SDL did not intialise. Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//setup passed so create a window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//check if window was created
		if (g_window == nullptr)
		{
			//window failed to create
			std::cout << "Window was not created. Error: " << SDL_GetError() << std::endl;
			return false;
		}
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (g_renderer != nullptr)
		{
			//init PNG Loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags)& imageFlags))
			{
				std::cout << "SDL_Image could not initialise. Errror: " << IMG_GetError() << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Renderer Could not intialise. Error: " << SDL_GetError() << std::endl;
			return false;
		}
		
		SDL_Joystick* joy = nullptr;
		if(SDL_JoystickOpen(0) == NULL)
		{
			std::cout << "Could not initialise joystick 1. Error: " << SDL_GetError() << std::endl;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Failed to Initialise SDL_Mixer. ERROR: " << Mix_GetError() << std::endl;
		}

			return true;
	}
}
void CloseSDL()
{
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//quit SDL Subsystems
	SDL_Quit();
}


