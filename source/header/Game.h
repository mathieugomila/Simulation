#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Console.h"
#include "Shader.h"
#include "GraphicalObject.h"

typedef struct window {
   GLFWwindow* ID;
   int width;
   int height;
} window_t;

int gameSetup(window_t* window);
int gameLoadContent(GLuint* shader, float* vertices, GLuint* vaoID);
int gameUpdate(window_t* window);
int gameDraw(window_t* window, GLuint* shader, GLuint* vaoID);
int gameTerminate();


#endif