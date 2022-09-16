#include "PlayerObject.h"

PlayerObject::PlayerObject(glm::vec2 position, BodyPos bodyPart)
{
	this->objectSize = glm::vec2(50.0f, 50.0f);
	this->objectLocation = position;

	if (bodyPart == HEAD)
	{
		this->moveDir = RIGHT; // Default movement i want to be right
		this->bodyPos = HEAD;
	}
	else
	{
		this->moveDir = RIGHT; // Default
		this->bodyPos = bodyPart;
	}
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::PlayerMove(GLuint height, GLuint width)
{
    if (this->moveDir == UP)
    {
        this->objectLocation.y -= 50;
        if (this->objectLocation.y <= -1.0f)
        {
            this->objectLocation.y += static_cast<GLfloat>(height);
        }
    }
    else if (this->moveDir == DOWN)
    {
        this->objectLocation.y += 50;
        if (this->objectLocation.y >= static_cast<GLfloat>(height))
        {
            this->objectLocation.y -= static_cast<GLfloat>(height);
        }
    }
    else if (this->moveDir == LEFT)
    {
        this->objectLocation.x -= 50;
        if (this->objectLocation.x <= -1.0f)
        {
            this->objectLocation.x += static_cast<GLfloat>(width);
        }
    }
    else if (this->moveDir == RIGHT)
    {
        this->objectLocation.x += 50;
        if (this->objectLocation.x >= static_cast<GLfloat>(width))
        {
            this->objectLocation.x -= static_cast<GLfloat>(width);
        }
    }
}

glm::vec2 PlayerObject::ProjectedPlayerMove(GLuint height, GLuint width)
{
    glm::vec2 tempCoord = this->objectLocation;
    if (this->moveDir == UP)
    {
        tempCoord.y -= 50;
        if (tempCoord.y <= -1.0f)
        {
            tempCoord.y += static_cast<GLfloat>(height);
        }
    }
    else if (this->moveDir == DOWN)
    {
        tempCoord.y += 50;
        if (tempCoord.y >= static_cast<GLfloat>(height))
        {
            tempCoord.y -= static_cast<GLfloat>(height);
        }
    }
    else if (this->moveDir == LEFT)
    {
        tempCoord.x -= 50;
        if (tempCoord.x <= -1.0f)
        {
            tempCoord.x += static_cast<GLfloat>(width);
        }
    }
    else if (this->moveDir == RIGHT)
    {
        tempCoord.x += 50;
        if (tempCoord.x >= static_cast<GLfloat>(width))
        {
            tempCoord.x -= static_cast<GLfloat>(width);
        }
    }
    return tempCoord;
}

void PlayerObject::UpdateLocation()
{

}

void PlayerObject::UpdateDirection(MoveDir checkDir)
{
	if (checkDir == UP)
	{
        if (!(this->moveDir == DOWN))
        {
            this->moveDir = UP;
        }
	}
	else if (checkDir == DOWN)
	{
        if (!(this->moveDir == UP))
        {
            this->moveDir = DOWN;
        }
	}
    else if (checkDir == RIGHT)
    {
        if (!(this->moveDir == RIGHT))
        {
            this->moveDir = LEFT;
        }
    }
    else if (checkDir == LEFT)
    {
        if (!(this->moveDir == LEFT))
        {
            this->moveDir = RIGHT;
        }
    }
}

void PlayerObject::UpdateBody(BodyPos newPos)
{
    this->bodyPos = newPos;
}
