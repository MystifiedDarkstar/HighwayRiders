#pragma once

#ifndef _PLAYERCHARACTER_H
#define _PLAYERCHARACTER_H

#include "GameObject.h"
#include "Constants.h"
#include "Level1Globals.h"

class GameScreenLevel1;

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, Level1Globals* lvl1Globals, Colour carColour);
	~PlayerCharacter();

	virtual void Render() override;
	virtual void Update(float deltaTime , SDL_Event e) override;

private:
	Level1Globals* m_lvl1Globals;
	Colour m_carColour;

	// tracks are zero indexed, player starts on first track up from the bottom. Bottom Track = 0, Next track = 1, Track next to top = 2, top track is 3
	int m_currentPlayerTrack = 1; 

	bool m_downKeyPressed = false;
	bool m_upKeyPressed = false;
	float m_inputTimer = 0.1f;

protected:

	virtual void MoveUpTrack(float deltaTime);
	virtual void MoveDownTrack(float deltaTime);

};

#endif // !_PLAYERCHARACTER_H