#include "header/Particules.h"

state *createParticule(){
    state *particuleState = malloc(sizeof(state));
    particuleState->position[0] = (float)rand() / (float)RAND_MAX;
    particuleState->position[1] = (float)rand() / (float)RAND_MAX;
    particuleState->direction[0] = 2 * (float)rand() / (float)RAND_MAX - 1;
    particuleState->direction[1] = 2 * (float)rand() / (float)RAND_MAX - 1;
    float normDirection = (float)sqrt(  particuleState->direction[0] * particuleState->direction[0] + 
                                        particuleState->direction[1] * particuleState->direction[1]);
    particuleState->direction[0] /= normDirection;
    particuleState->direction[1] /= normDirection;

    particuleState->size = 0.1;

    return particuleState;
}


float* createParticuleVerticesArray(state* particuleState){
    float *vertices = malloc(12 * sizeof(float));
    vertices[0] = -particuleState->size/2;
    vertices[1] = particuleState->size/2;
    vertices[2] = particuleState->size/2;
    vertices[3] = particuleState->size/2;
    vertices[4] = -particuleState->size/2;
    vertices[5] = -particuleState->size/2;
    vertices[6] = -particuleState->size/2;
    vertices[7] = -particuleState->size/2;
    vertices[8] = particuleState->size/2;
    vertices[9] = particuleState->size/2;
    vertices[10] = particuleState->size/2;
    vertices[11] = -particuleState->size/2;

    return vertices;
}

static float distanceBetweenParticules(state* state1, state* state2){
    float deltaX = state1->position[0]-state2->position[0];
    float deltaY = state1->position[1]-state2->position[1];
    return (float)sqrt(deltaX * deltaX + deltaY * deltaY);
}

static void checkCollision(state* state1, state* state2){
    // if collision
    float distance = distanceBetweenParticules(state1, state2);
    if(distance <= state1->size/2 + state2->size/2){
        float collisionDirection[2] = { (state2->position[0] - state1->position[0])/distance, 
                                        (state2->position[1] - state1->position[1])/distance};
        
        // update direction of movement
        state2->direction[0] = collisionDirection[0];
        state2->direction[1] = collisionDirection[1];
        state1->direction[0] = -collisionDirection[0];
        state1->direction[1] = -collisionDirection[1];
    }
}


void checkAllCollision(state** allParticulesStates, int nbrOfParticules){
    for(int i = 0; i < nbrOfParticules; i++){
        for(int j = i + 1; j < nbrOfParticules; j++){
            checkCollision(allParticulesStates[i], allParticulesStates[j]);
        }
    }
}

static void checkBoundaries(state* state){
    // if on left side
    if(state->position[0] < -1){
        state->direction[0] *= -1;
    }
    // if on top side
    if(state->position[1] > 1){
        state->direction[1] *= -1;
    }
    // if on right side
    if(state->position[0] > 1){
        state->direction[0] *= -1;
    }
    // if on bottom side
    if(state->position[1] < -1){
        state->direction[1] *= -1;
    }


}

void checkAllBoundaries(state** allParticulesStates, int nbrOfParticules){
    for(int i = 0; i < nbrOfParticules; i++){
        checkBoundaries(allParticulesStates[i]);
    }
}