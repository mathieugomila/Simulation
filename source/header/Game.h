#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Console.h"
#include "Shader.h"
#include "GraphicalObject.h"
#include "Particules.h"
#include "Camera.h"

typedef struct window {
   GLFWwindow* ID;
   int width;
   int height;
} window_t;

int gameSetup(window_t* window);
int gameLoadContent(GLuint* shader, float* vertices, GLuint* vaoID, state** allParticulesStates, int nbrOfParticules);
int gameUpdate(window_t* window, state** allParticulesStates, int nbrOfParticules);
int gameDraw(window_t* window, GLuint* shader, GLuint* vaoID, float* color, state** allParticulesStates, int nbrOfParticules);
int gameTerminate();


#endif