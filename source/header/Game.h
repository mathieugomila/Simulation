#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Console.h"
#include "Shader.h"

typedef struct window {
   GLFWwindow* ID;
   int width;
   int height;
} window_t;

int gameSetup(window_t* window);
int gameLoadContent();
int gameUpdate();
int gameDraw();
int gameTerminate();


#endif