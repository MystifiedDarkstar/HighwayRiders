#include "Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{
    m_ViewBox = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Camera::Update(float deltaTime)
{
    // check we have a valid target
    if (m_Target != nullptr)
    {
        m_ViewBox.x = 0;
        m_ViewBox.y = m_Target->y - SCREEN_HEIGHT / 5;

        if (m_ViewBox.x < 0)
        {
            m_ViewBox.x = 0;
        }
        if (m_ViewBox.y < 0)
        {
            m_ViewBox.y = 0;
        }
        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}
