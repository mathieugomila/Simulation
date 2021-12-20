#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Console.h"
#include "Shader.h"

void updatePerspectiveCamera(GLuint shader);

#endif