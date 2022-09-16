#include "Map.h"

#include <iostream>

Map::Map(GLuint width, GLuint height, glm::vec2 playerSize, glm::vec2 playerStartCoord)
{
	this->takenCoords.push_back(glm::vec2(playerStartCoord.x / playerSize.x, playerStartCoord.y / playerSize.y));

	this->row_max = glm::vec2(static_cast<float>(width) / playerSize.x, static_cast<float>(height) / playerSize.y);

    // tile map init
    CreateMap();
}

Map::~Map()
{

}

void Map::CreateMap()
{
    for (int i = 0; i < this->row_max.y; i++)
    {
        std::vector<int> temp;
        this->tileMap.push_back(temp);
        for (int j = 0; j < this->row_max.x; j++)
        {
            this->tileMap[i].push_back(0);
        }
    }
}

void Map::UpdateMap(std::vector<PlayerObject> players)
{
    std::cout << players.size() << std::endl;
    for (int i = 0; i < players.size();i++)
    {
        tileMap[takenCoords[i].y][takenCoords[i].x] = 0;
        takenCoords[i].y = players[i].objectLocation.y / players[i].objectSize.y;
        takenCoords[i].x = players[i].objectLocation.x / players[i].objectSize.x;
        tileMap[takenCoords[i].y][takenCoords[i].x] = 1;
    }
    // Output to console for visualization
    std::cout << "-------------------------------------------------------" << std::endl;
    for (int i = 0; i < this->row_max.y; i++)
    {
        for (int j = 0; j < this->row_max.x; j++)
        {
            std::cout << this->tileMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
