#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.h"
#include "ResourceManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//GLuint ShaderCompileFromFile(const char* vShaderFile, const char* fShaderFile);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Screen size 
const GLuint Scr_H = 800;
const GLuint Scr_W = 800;

Game Breakout(Scr_H, Scr_W);

//Direction direction;

int main(int argc, char* argv[])
{
	// Flags memory leaks (always include in projects to detect)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	glfwInit();

	// OpenGL V3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Needed to work on Apple OS
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, false);

	// Init GLFW
	GLFWwindow* window = glfwCreateWindow(Scr_H, Scr_W, "khaled's Snake", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// OpenGL Config
	glViewport(0, 0, Scr_H, Scr_W);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//// Shader comp
	//GLuint shaderProgram = ShaderCompileFromFile("shaders/sprite.vs", "shaders/sprite.fs");


	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Scr_W), static_cast<float>(Scr_H), 0.0f, -1.0f, 1.0f);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, false, glm::value_ptr(projection));

	//// VAO/VBO setup
	////GLfloat vertices[] =
	////{
	////	-0.5f,  0.5f, 0.0f,	// top left
	////	-0.5f, -0.5f, 0.0f, // bottom left  
	////	 0.5f,  0.5f, 0.0f, // top right
	////	 0.5f, -0.5f, 0.0f  // bottom right		
	////};
	//GLfloat vertices[] = 
	//{
	//	// pos      // tex
	//	0.0f, 1.0f,
	//	1.0f, 0.0f,
	//	0.0f, 0.0f,

	//	0.0f, 1.0f,
	//	1.0f, 1.0f,
	//	1.0f, 0.0f
	//};
	////GLuint indices[]
	////{
	////	2, 3, 0,		// First triangle
	////	3, 1, 0		// Second triangle
	////};

	//GLuint VBO, VAO; // EBO

	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	////glGenBuffers(1, &EBO);

	////glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindVertexArray(VAO);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	// initialize game
	// ---------------
	Breakout.Init();

	// deltaTime vars
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Program loop
	while (!glfwWindowShouldClose(window))
	{
		// dt calculation
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// manage user input
		// -----------------
		Breakout.ProcessInput(deltaTime);

		// update game state
		// -----------------
		Breakout.Update(deltaTime);

		// Check for inputs
		/*processInput(window);*/

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);


		//glUseProgram(shaderProgram);
		//glm::mat4 model = glm::mat4(1.0f);
		////position += velocity * deltaTime;
		////model = glm::translate(model, glm::vec3(size, 0.0f));
		////model = glm::scale(model, glm::vec3(size, 1.0f));
		//model = glm::translate(model, glm::vec3(position, 0.0f));
		//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		//model = glm::scale(model, glm::vec3(size, 1.0f));
		//GLuint location = glGetUniformLocation(shaderProgram, "model");
		//glUniformMatrix4fv(location, 1, false, glm::value_ptr(model));
		////this->shader.SetMatrix4("model", model);

		//// Render
		//glBindVertexArray(VAO);
		///*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glBindVertexArray(0);

		//// send new frame to window
		//glfwSwapBuffers(window);
		//glfwPollEvents();
	}

	// destruct
	// delete all resources as loaded using the resource manager
	// ---------------------------------------------------------
	ResourceManager::Clear();
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	////glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//		std::cout << "Window closed using escape!" << std::endl;
//	}
//	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	//{
//	//	if (!(direction == DOWN))
//	//	{
//	//		velocity = glm::vec2(0.0f, 3.0f);
//	//		direction = UP;
//	//	}
//	//}
//	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	//{
//	//	if (!(direction == UP))
//	//	{
//	//		velocity = glm::vec2(0.0f, -3.0f);
//	//		direction = DOWN;
//	//	}
//	//}
//	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	//{
//	//	if (!(direction == RIGHT))
//	//	{
//	//		velocity = glm::vec2(-3.0f, 0.0f);
//	//		direction = LEFT;
//	//	}
//	//}
//	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	//{
//	//	if (!(direction == LEFT))
//	//	{
//	//		velocity = glm::vec2(3.0f, 0.0f);
//	//		direction = RIGHT;
//	//	}
//	//}
//}
//
//GLuint ShaderCompileFromFile(const char* vShaderFile, const char* fShaderFile)
//{
//	// 1. retrieve the vertex/fragment source code from filePath
//	std::string vertexCode;
//	std::string fragmentCode;
//	try
//	{
//		// open files
//		std::ifstream vertexShaderFile(vShaderFile);
//		std::ifstream fragmentShaderFile(fShaderFile);
//		std::stringstream vShaderStream, fShaderStream;
//		// read file's buffer contents into streams
//		vShaderStream << vertexShaderFile.rdbuf();
//		fShaderStream << fragmentShaderFile.rdbuf();
//		// close file handlers
//		vertexShaderFile.close();
//		fragmentShaderFile.close();
//		// convert stream into string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//	}
//	catch (std::exception e)
//	{
//		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
//	}
//	const char* vShaderCode = vertexCode.c_str();
//	const char* fShaderCode = fragmentCode.c_str();
//	// 2. now create shader object from source code
//
//	// Shader comp
//	GLuint vShader, fShader;
//
//	vShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vShader, 1, &vShaderCode, NULL);
//	glCompileShader(vShader);
//
//	// check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// Fragment shader comp
//	fShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fShader, 1, &fShaderCode, NULL);
//	glCompileShader(fShader);
//	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
//	// check for shader compile errors
//	if (!success)
//	{
//		glGetShaderInfoLog(fShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// Shader program comp
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vShader);
//	glAttachShader(shaderProgram, fShader);
//	glLinkProgram(shaderProgram);
//	if (!success)
//	{
//		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vShader);
//	glDeleteShader(fShader);
//
//	return shaderProgram;
//}
