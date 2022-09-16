#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <list>

#include "PlayerObject.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    GLboolean               Keys[1024];
    GLuint                  width, height;
    GLfloat                 RunTime;
    GLboolean               pickedUp;
    GLfloat                 speed;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    // game methods (move these later to new class PlayerHandler)
    void ResetGame();
    PlayerObject AddToSnake(glm::vec2 coord, BodyPos body_pos);
    void SwapSnakeParts(PlayerObject partOne, PlayerObject PartTwo);
    void CheckIfLost();
    
};

#endif