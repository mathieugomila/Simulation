#ifndef PARTICULE_H
#define PARTICULE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cglm/cglm.h>

#include "Console.h"

typedef struct{
    float position[3];
    float direction[3];
    float size;
} state;

state *createParticule();
float* createParticuleVerticesArray(state* particuleState);
void checkAllCollision(state** allParticulesStates, int nbrOfParticules);
void checkAllBoundaries(state** allParticulesStates, int nbrOfParticules);

#endif