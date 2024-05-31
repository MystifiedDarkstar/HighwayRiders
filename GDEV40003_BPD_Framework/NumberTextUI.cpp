#include "NumberTextUI.h"

NumberTextUI::NumberTextUI(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}

NumberTextUI::~NumberTextUI()
{
    for (int i = 0; i < m_textTextures.size(); i++)
    {
        delete m_textTextures[i];
    }
    m_textTextures.clear();
}

void NumberTextUI::SetUpText(std::string text, int size)
{
    // LOAD BACKGROUND TEXTURE
    m_timeBackground = new Texture2D(m_renderer);
    if (size == 1)
    {
        if (!m_timeBackground->LoadFromFile("Assets/Images/T_TimeBackgroundSize1.png"))
        {
            std::cout << "Failed to load image; T_TimeBackgroundSize1" << std::endl;
        }
    }
    else
    {
        if (!m_timeBackground->LoadFromFile("Assets/Images/T_TimeBackgroundSize2.png"))
        {
            std::cout << "Failed to load image; T_TimeBackgroundSize2" << std::endl;
        }
    }
    
    //CREATE AND STORE TEXTURES NEEDED TO DISPLAY TIME TEXT
    for(int i = 0; i < text.length(); i++)
    {
        Texture2D* tempTexture = new Texture2D(m_renderer);
        m_textTextures.push_back(tempTexture);
    }

    UpdateText(text,size);
}

void NumberTextUI::LoadNumberTextInfo(float time)
{
    int temp = std::floor(time);
    int minutesTenth,minutesUnit,secondsTenth,secondsUnit;
    
    int tempMins = temp / 60;
    minutesTenth = tempMins / 10;
    tempMins -= minutesTenth * 10;
    minutesUnit = tempMins;
        
    temp -= tempMins * 60;
        
    int tempSecs = temp;
    secondsTenth = temp / 10;
    tempSecs -= secondsTenth * 10;
    secondsUnit = tempSecs;
        
    if (time > m_lastTextUpdate)
    {
        std::string outputTime = std::to_string(minutesTenth) + std::to_string(minutesUnit) + ":" + std::to_string(secondsTenth) + std::to_string(secondsUnit);      
        UpdateText(outputTime, 1);
        m_lastTextUpdate = time;
    }
}

void NumberTextUI::UpdateText(std::string text, int size)
{
    int sizeCount = 0;
    if (size == 2)
    {
        sizeCount = 11;
    }
    for(int i = 0; i < text.length(); i++)
    {
        switch (text[i])
        {
        case '0':
            if(!m_textTextures[i]->LoadFromFile(m_TexturePaths[0 + sizeCount]))
            {
                std::cout << "Failed to load image; T_ZeroSize" << size << std::endl;
            }
            break;
        case '1':
            if(!m_textTextures[i]->LoadFromFile(m_TexturePaths[1 + sizeCount]))
            {
                std::cout << "Failed to load image; T_OneSize" << size << std::endl;
            }
            break;
        case '2':
            if(!m_textTextures[i]->LoadFromFile(m_TexturePaths[2 + sizeCount]))
            {
                std::cout << "Failed to load image; T_TwoSize" << size << std::endl;
            }
            break;
        case '3':
            if(!m_textTextures[i]->LoadFromFile(m_TexturePaths[3 + sizeCount]))
            {
                std::cout << "Failed to load image; T_ThreeSize" << size << std::endl;
            }
            break;
        case '4':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[4 + sizeCount]))
            {
                std::cout << "Failed to load image; T_FourSize" << size << std::endl;
            } 
            break;
        case '5':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[5 + sizeCount]))
            {
                std::cout << "Failed to load image; T_FiveSize" << size << std::endl;
            }
            break;
        case '6':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[6 + sizeCount]))
            {
                std::cout << "Failed to load image; T_SixSize" << size << std::endl;
            }
            break;
        case '7':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[7 + sizeCount]))
            {
                std::cout << "Failed to load image; T_SevenSize" << size << std::endl;
            }
            break;
        case '8':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[8 + sizeCount]))
            {
                std::cout << "Failed to load image; T_EightSize" << size << std::endl;
            }
            break;
        case '9':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[9 + sizeCount]))
            {
                std::cout << "Failed to load image; T_NineSize" << size << std::endl;
            }
            break;
        case ':':
            if (!m_textTextures[i]->LoadFromFile(m_TexturePaths[10 + sizeCount]))
            {
                std::cout << "Failed to load image; T_TenSize" << size << std::endl;
            }
            break;
        default:
            std::cout << "ERROR: Char was not recognised, cannot load char: " << text[i] << std::endl;
            break;
        }
    }
}

void NumberTextUI::Update(float deltaTime, SDL_Event e)
{
    
}

void NumberTextUI::Render(Vector2D renderStartPos)
{
    m_timeBackground->Render(renderStartPos, SDL_FLIP_NONE, 0);
    for (int i = 0; i < m_textTextures.size();i++)
    {
        m_textTextures[i]->Render(Vector2D(renderStartPos.x + (i * m_textTextures[i]->GetWidth()), renderStartPos.y + 5) , SDL_FLIP_NONE , 0);
    }
}

std::string NumberTextUI::m_TexturePaths[] =
{
    "Assets/Images/T_Zero.png",  // 0
    "Assets/Images/T_One.png",   // 1
    "Assets/Images/T_Two.png",   // 2
    "Assets/Images/T_Three.png", // 3
    "Assets/Images/T_Four.png",  // 4
    "Assets/Images/T_Five.png",  // 5
    "Assets/Images/T_Six.png",   // 6
    "Assets/Images/T_Seven.png", // 7
    "Assets/Images/T_Eight.png", // 8
    "Assets/Images/T_Nine.png",  // 9
    "Assets/Images/T_Colon.png", // :
    "Assets/Images/T_ZeroSize2.png",  // 0 Size 2
    "Assets/Images/T_OneSize2.png",   // 1 Size 2
    "Assets/Images/T_TwoSize2.png",   // 2 Size 2
    "Assets/Images/T_ThreeSize2.png", // 3 Size 2
    "Assets/Images/T_FourSize2.png",  // 4 Size 2
    "Assets/Images/T_FiveSize2.png",  // 5 Size 2
    "Assets/Images/T_SixSize2.png",   // 6 Size 2
    "Assets/Images/T_SevenSize2.png", // 7 Size 2
    "Assets/Images/T_EightSize2.png", // 8 Size 2
    "Assets/Images/T_NineSize2.png",  // 9 Size 2
    "Assets/Images/T_ColonSize2.png"  // : Size 2
    };