#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:
	// Variables
	glm::vec2               objectSize;
	glm::vec2               objectLocation;
	// constructor/destructor
	GameObject();
	~GameObject();
	// Methods
private:
	// Variables

	// Methods
};

#endif