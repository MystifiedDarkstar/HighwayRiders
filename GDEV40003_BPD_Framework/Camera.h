#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "SDL.h"
#include "Commons.h"
#include "Constants.h"

class Camera
{
public:

    void Update(float deltaTime);
    inline static Camera* GetInstance(){return m_Instance = (m_Instance != nullptr) ? m_Instance : new Camera();}
    inline SDL_Rect GetViewBox(){return m_ViewBox;}
    inline Vector2D GetPosition(){return m_Position;}
    inline void SetTarget(Vector2D* target) {m_Target = target;}
    inline void ResetCamera() { m_Position = Vector2D(0, 0);}
    
private:
    Camera();

    Vector2D* m_Target = nullptr; // current target camera is following
    Vector2D m_Position; // current position of the camera
    
    SDL_Rect m_ViewBox; // size of the camera view
    static Camera* m_Instance; // Instance of camera 
};
#endif