#pragma once
//Screen Dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

// LEVEL 1 CONSTANTS
#define BACKGROUND_WIDTH 1600 // THE WIDTH OF A SINGULAR BACKGROUND
#define BACKGROUND_COUNT 2 // THE NUMBER OF BACKGROUNDS PRESPAWNED IN LEVEL 1 FOR SCROLLING BACKGROUND

#define OFFSCREEN_SPAWN_XPOS 900 // THE SPAWN POSITION ON X AXIS FOR OBJECTS SUCH AS OBSTACLES / COINS TO BE OUT OF VIEW

#define LEVEL1_LANES 3 // THE NUMBER OF LANES IN THE GAME MINUS 1, Lanes are zero-Indexed.
#define LANE_WIDTH 64 // THE Y WIDTH OF 1 LANE
#define TOP_LANE_YPOS 320 // Y POSITION OF TOP LANE

#define SCROLL_SPEED 350.0f

//TEXTURE PATHS

#define TPATH_REDCAR "Assets/Images/T_Car.png"
#define TPATH_PREVIEWCAR "Assets/Images/T_CustomisationCar.png"
#define TPATH_OBSTACLE_ROCK1 "Assets/Images/T_Obstacle.png"
#define TPATH_OBSTACLE_ROCK2 "Assets/Images/T_Obstacle1.png"
#define TPATH_OBSTACLE_ROCK3 "Assets/Images/T_Obstacle2.png"
#define TPATH_COLLECTABLE_COIN1 "Assets/Images/T_Coin.png"

#define TPATH_POWERUP_DEFAULT "Assets/Images/T_DefaultPowerUP.png"
#define TPATH_POWERUP_SPEEDUP "Assets/Images/T_SpeedUP_PowerUP.png"
#define TPATH_POWERUP_SLOWDOWN "Assets/Images/T_SlowDown_PowerUP.png"
#define TPATH_POWERUP_2XMULTIPLIER "Assets/Images/T_2XMulti_PowerUP.png"
#define TPATH_POWERUP_5XMULTIPLIER "Assets/Images/T_5XMulti_PowerUP.png"

#define TPATH_UI_SMALLBOX "Assets/Images/T_UISmallBox.png"
#define TPATH_UI_LARGEBOX "Assets/Images/T_UILargeBox.png"

#define TPATH_BACKGROUND_TITLE "Assets/Images/T_MenuBackground.png"
#define TPATH_BACKGROUND_TITLETEXT "Assets/Images/T_MenuText.png"

#define TPATH_BACKGROUND_GAMEOVER "Assets/Images/T_GameOverBackground.png"
#define TPATH_BACKGROUND_GAMEOVERMENUTEXT "Assets/Images/T_GameOverMenuText.png"

#define TPATH_BACKGROUND_LEVEL1 "Assets/Images/T_Level1Background.png"

#define TPATH_BACKGROUND_CUSTOMISATION "Assets/Images/T_CustomisationBackground.png"

// FONT PATHS

#define TTFPATH_FRESHMAN "Assets/Fonts/Freshman.ttf"
#define TTFPATH_ROBOTO "Assets/Fonts/Roboto-Bold.ttf"

// FILE PATHS

#define FLPATH_SAVEINFO_LEVELTIME "SaveInfo/levelTime.txt"
#define FLPATH_SAVEINFO_HIGHSCORE "SaveInfo/highScore.txt"
#define FLPATH_SAVEINFO "SaveInfo/saveGame.txt"

// AUDIO PATHS

#define AUPATH_BACKGROUND_MUSIC "Assets/Audio/AF_BackgroundMusic.wav"
#define AUPATH_COIN_COLLECT "Assets/Audio/AF_CoinCollect.wav"

