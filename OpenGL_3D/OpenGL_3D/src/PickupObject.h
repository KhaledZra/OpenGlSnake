#ifndef PICKUP_OBJECT_H
#define PICKUP_OBJECT_H

#pragma region OpenGL_Includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma endregion OpenGL_Includes


#include "GameObject.h"
#include "PlayerObject.h"
#include <vector>

class PickupObject : public GameObject
{
public:
	// Variables
	GLboolean				isActive; // Keeps track of what object belongs to
	// constructor/destructor
	PickupObject();
	~PickupObject();
	// Methods
	void SpawnPickup(glm::vec2 rows, std::vector<PlayerObject> players);
	bool CheckPickedUp(glm::vec2 playerPos);
	bool EmptySpawnLocation(std::vector<PlayerObject> players);
};

#endif

