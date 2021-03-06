#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Console.h"

char* readVertexShader(const char* shaderName, int* shaderLength);
char* readFragmentShader(const char* shaderName, int* shaderLength);
GLuint compileShader(const char* shaderName);
GLuint compileVertexShader(const char* shaderName);
GLuint compileFragmentShader(const char* shaderName);
void useShader(GLuint shaderID);
void sendUniformValue3f(GLuint shader, char* name, float value[3]);
void sendUniformValue4x4(GLuint shader, char* name, mat4 value);

#endif