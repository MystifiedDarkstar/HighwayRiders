#pragma once
#include <iostream>

struct Vector2D
{
	float x;
	float y;

	inline Vector2D operator+(const Vector2D& v2) {return Vector2D(x + v2.x,y + v2.y);}
	friend inline Vector2D operator+=(Vector2D& v1, const Vector2D& v2) {v1.x += v2.x; v1.y += v2.y; return v1;}
	inline Vector2D operator-(const Vector2D& v2) {return Vector2D(x - v2.x,y - v2.y);}
	friend inline Vector2D operator-=(Vector2D& v1, const Vector2D& v2) {v1.x -= v2.x; v1.y -= v2.y; return v1;} 
	inline Vector2D operator*(const float scalar) {return Vector2D(x * scalar ,y * scalar);}
	inline void Log(std::string msg = " "){std::cout << msg << "(X , Y) (" << x << " , " << y << ")" << std::endl;}
	
	// DEFAULT CONSTRUCTOR
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	// PARAMETER CONSTRUCTOR
	Vector2D(float initial_x , float initial_y)
	{
		x = initial_x;
		y = initial_y;	
	}
};

struct Rect2D
{
	float xPos;
	float yPos;
	float width;
	float height;

	Rect2D(float newXPos, float newYPos, float newWidth, float newHeight)
	{
		xPos = newXPos;
		yPos = newYPos;
		width = newWidth;
		height = newHeight;
	}
};

enum SCREENS
{
	SCREEN_TITLE,
	SCREEN_GAMEOVER,
	SCREEN_LEVEL1,
	SCREEN_CUSTOMISATION
};

enum PowerUps
{
	NONE,
	SPEEDUP,
	SLOWDOWN,
	MULTIPLIERx2,
	MULTIPLIERx5
};

struct Colour
{
	int r, g, b;
};