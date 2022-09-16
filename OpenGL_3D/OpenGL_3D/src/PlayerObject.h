#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"

// Represents the current movement direction of the player
enum MoveDir {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
// Represents the current movement direction of the player
enum BodyPos {
	HEAD,
	BODY,
	TAIL
};

class PlayerObject : public GameObject
{
public:
	// Variables
	MoveDir                 moveDir; // Keeps track of what direction the head is moving
	BodyPos					bodyPos; // Keeps track of what object belongs to
	// constructor/destructor
	PlayerObject(glm::vec2 position, BodyPos bodyPart);
	~PlayerObject();
	// Methods
	void PlayerMove(GLuint height, GLuint width);
	glm::vec2 ProjectedPlayerMove(GLuint height, GLuint width);
	void UpdateLocation();
	void UpdateDirection(MoveDir checkDir);
	void UpdateBody(BodyPos newPos);
private:
	// Variables

	// Methods
};

#endif
