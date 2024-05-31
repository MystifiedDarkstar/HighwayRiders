#pragma once
#ifndef _CARCUSTOMISATIONSCREEN_H
#define _CARCUSTOMISATIONSCREEN_H

#include "GameScreen.h"
#include "SaveGame.h"
#include "GUIText.h";
#include "Background.h"
#include "Texture2D.h"
#include "Commons.h"

class CarCustomisationScreen : GameScreen
{
public:
	CarCustomisationScreen(SDL_Renderer* renderer);
	~CarCustomisationScreen() override;

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpLevel();

	void IncreaseColourCount();
	void DecreaseColourCount();

	void MoveLeftColour();
	void MoveRightColour();

private:
	Background* m_background;

	GUIText* m_redValueText;
	GUIText* m_blueValueText;
	GUIText* m_greenValueText;

	Texture2D* m_previewCar;

	Colour m_previewCarColor;

	bool m_upKeyPressed = false;
	bool m_downKeyPressed = false;

	float m_inputTimer = 0.1f;

	int m_selectedColour = 0; // 0 == red, 1 == green, 2 == blue
};


#endif // !_CARCUSTOMISATIONSCREEN_H