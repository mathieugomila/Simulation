#ifndef GRAPHICAL_OBJECT_H
#define GRAPHICAL_OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint createVAO(float* vertices, int nbrVertices);
void drawVAO(GLuint vaoID, int nbrVertices);

#endif