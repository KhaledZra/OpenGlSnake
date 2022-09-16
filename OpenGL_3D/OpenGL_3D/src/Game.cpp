#include <iostream>
#include <vector>

#include "Game.h"

#pragma region Class_Includes
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"
#include "Map.h"
#include "PickupObject.h"
#pragma endregion Class_Includes

// Game-related State data
SpriteRenderer* Renderer;
Map* map;
PickupObject* pickupObject;

std::vector<PlayerObject> Players = std::vector<PlayerObject>();

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), width(width), height(height)
{
    this->RunTime = 0.0f;
    this->pickedUp = false;
    this->speed = 0.5f;
}

Game::~Game()
{
    delete Renderer;
    delete map;
    delete pickupObject;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    std::cout << "Shaders/shader successfully initialized!" << std::endl;
    // set render-specific controls
    Shader temp = Shader(ResourceManager::GetShader("sprite"));
    Renderer = new SpriteRenderer(temp);
    // load textures
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    std::cout << "Textures/texture successfully initialized!" << std::endl;

    // init first snake head
    Players.push_back(AddToSnake(glm::vec2(this->width / 2, this->height / 2),HEAD));
    std::cout << "Snake head successfully initialized!" << std::endl;

    // init map
    map = new Map(this->width, this->height, Players.front().objectSize, Players.front().objectLocation);
    std::cout << "Map successfully initialized!" << std::endl;

    pickupObject = new PickupObject();
    std::cout << "Pickup Object successfully initialized!" << std::endl;
}

void Game::Update(float dt)
{
    RunTime += dt;


    
	if (RunTime >= speed)
	{
        // front will always be the head part of the snake
        if (Players.size() == 1)
        {
            Players[0].PlayerMove(this->height, this->width);
        }
        else
        {
            for (int i = Players.size()-1; i > 0; i--)
            {
                Players[i].objectLocation = Players[i - 1].objectLocation;
            }
            Players[0].PlayerMove(this->height, this->width);
        }

        // TODO fix up code and potentially create a player handler class that takes care of all movement
        // TODO gl future me :)

        // Spawn Pickup Object
        pickupObject->SpawnPickup(map->row_max, Players);

        CheckIfLost();

        // Check if picked up
        pickedUp = pickupObject->CheckPickedUp(Players[0].objectLocation);
        if (pickedUp)
        {
            Players.push_back(AddToSnake(Players[Players.size() - 1].objectLocation, TAIL));
            if (speed > 0.05f)
            {
                speed = speed - 0.03f;
            }
        }

        //// Update map
        //map->UpdateMap(Players);

        // Reset
        RunTime = 0.0f;
	}
}

void Game::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_W])
	{
        Players[0].UpdateDirection(UP);
	}
    if (this->Keys[GLFW_KEY_S])
    {
        Players[0].UpdateDirection(DOWN);
    }
    if (this->Keys[GLFW_KEY_A])
    {
        Players[0].UpdateDirection(RIGHT);
    }
    if (this->Keys[GLFW_KEY_D])
    {
        Players[0].UpdateDirection(LEFT);
    }
}

void Game::Render()
{
    Texture2D temp = Texture2D(ResourceManager::GetTexture("face"));
    //GLfloat mid_W = 0;
    //GLfloat mid_H = (Height / 2) + 50.0f;
    //GLfloat tempLoc = mid_W;
    //for (int i = 0; i < 16; i++)
    //{
    //    Renderer->DrawSprite(temp, glm::vec2(tempLoc, mid_H), glm::vec2(50.0f, 50.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //    tempLoc += 50.0f;
    //}

    // Draw Snake
    for (int i = 0; i < Players.size(); i++)
    {
        Renderer->DrawSprite(temp, Players[i].objectLocation, Players[i].objectSize, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Draw Pickup
    if (pickupObject->isActive == true)
    {
        Renderer->DrawSprite(temp, pickupObject->objectLocation, pickupObject->objectSize, 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }

}

void Game::ResetGame()
{
    //For debugging
    std::cout << "You lost!" << std::endl;

    // reset snake
    Players.clear();
    Players.push_back(AddToSnake(glm::vec2(this->width / 2, this->height / 2), HEAD));

    // reset pickup location
    pickupObject->isActive = false;

    // reset speed
    this->speed = 0.5f;
}

PlayerObject Game::AddToSnake(glm::vec2 coord, BodyPos body_pos)
{
    PlayerObject playerObject(coord, body_pos);
    return playerObject;
}

void Game::CheckIfLost()
{
    for (int i = 1; i < Players.size();i++)
    {
        // Check if head has hit a another bodypart
	    if (Players[0].objectLocation == Players[i].objectLocation)
	    {
            ResetGame();
	    }
    }
}
