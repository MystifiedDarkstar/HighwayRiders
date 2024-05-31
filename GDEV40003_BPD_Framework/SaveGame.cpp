#include "SaveGame.h"
#include <iostream>
#include <fstream>

SaveGame* SaveGame::m_instance;

SaveGame::SaveGame()
{

}

void SaveGame::LoadSaveData()
{
    std::ifstream saveGameFile;
    saveGameFile.open(FLPATH_SAVEINFO);

    if (saveGameFile.is_open())
    {
        saveGameFile >> m_levelAllTime;
        saveGameFile >> m_highScore;
        saveGameFile >> m_playerColour.r;
        saveGameFile >> m_playerColour.g;
        saveGameFile >> m_playerColour.b;
        std::cout << "R: " << m_playerColour.r << " G: " << m_playerColour.g << " B: " << m_playerColour.b << std::endl;
        saveGameFile.close();
    }
    else std::cout << "Error: File was not open, Could not read. Filename: levelTime.txt\n";
}

void SaveGame::WriteSaveData()
{
    std::ofstream saveGameFile;
    saveGameFile.open(FLPATH_SAVEINFO);

    if (saveGameFile.is_open())
    {
        saveGameFile << m_levelAllTime << "\n";
        saveGameFile << m_highScore << "\n";
        saveGameFile << m_playerColour.r << "\n";
        saveGameFile << m_playerColour.g << "\n";
        saveGameFile << m_playerColour.b;
        saveGameFile.close();
    }
    else std::cout << "Error: File was not open, Could not read. Filename: levelTime.txt\n";
}
