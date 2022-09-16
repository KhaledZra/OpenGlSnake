#include "PickupObject.h"

#include <iostream>
#include <time.h>

PickupObject::PickupObject()
{
	// Initializing class variables
	this->isActive = false;
	// Initializing inherited variables
	this->objectSize = glm::vec2(50.0f, 50.0f);
	this->objectLocation = glm::vec2(0.0f, 0.0f);

	// Initialize srand on current time
	srand(time(0));
}

PickupObject::~PickupObject()
{

}

void PickupObject::SpawnPickup(glm::vec2 rows, std::vector<PlayerObject> players)
{
	if (isActive == false)
	{
		do
		{
			this->objectLocation.y = (rand() % static_cast<int>(rows.y)) * this->objectSize.y;
			this->objectLocation.x = (rand() % static_cast<int>(rows.x)) * this->objectSize.x;
		} while (EmptySpawnLocation(players) == true);

		// Display for debugging reasons
		std::cout << "Pickup spawned at Coord: " << objectLocation.y << "," << objectLocation.x << std::endl;

		// Set active
		this->isActive = true;
	}
}

bool PickupObject::CheckPickedUp(glm::vec2 playerPos)
{
	if (isActive == true)
	{
		if (playerPos == this->objectLocation)
		{
			// Hit, Destroy/Set unactive
			//TODO Send information to increase player size
			isActive = false;
			return true;
		}
	}
	return false;
}

bool PickupObject::EmptySpawnLocation(std::vector<PlayerObject> players)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].objectLocation == this->objectLocation)
		{
			return true;
		}
	}
	return false;
}
