#ifndef MAP_H
#define MAP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "PlayerObject.h"

#include <list>

class Map
{
public:
	// Variables
	glm::vec2						row_max;
	std::vector<glm::vec2>			takenCoords;
	std::vector<std::vector<int>>	tileMap;
	// Constructor/Destructor
	Map(GLuint width, GLuint height, glm::vec2 playerSize, glm::vec2 playerStartCoord);
	~Map();
	// Methods
	void CreateMap();
	void UpdateMap(std::vector<PlayerObject> players);
};

#endif