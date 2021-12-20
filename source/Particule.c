#include "header/Particules.h"

state *createParticule(){
    state *particuleState = malloc(sizeof(state));
    particuleState->position[0] = (float)rand() / (float)RAND_MAX;
    particuleState->position[1] = (float)rand() / (float)RAND_MAX;
    particuleState->position[2] = (float)rand() / (float)RAND_MAX;
    particuleState->direction[0] = (float)rand() / (float)RAND_MAX;
    particuleState->direction[1] = (float)rand() / (float)RAND_MAX;
    particuleState->direction[2] = (float)rand() / (float)RAND_MAX;
    float normDirection = (float)sqrt(  particuleState->direction[0] * particuleState->direction[0] + 
                                        particuleState->direction[1] * particuleState->direction[1] +
                                        particuleState->direction[2] * particuleState->direction[2]);
    particuleState->direction[0] /= normDirection;
    particuleState->direction[1] /= normDirection;
    particuleState->direction[2] /= normDirection;

    particuleState->size = 0.1;

    return particuleState;
}

static float verticesCubes[3 * 36] =   {0, 0, 0, 0, 1, 0, 1, 0, 0, // front
                                        1, 0, 0, 0, 1, 0, 1, 1, 0,

                                        1, 0, 0, 1, 1, 0, 1, 0, 1, // right
                                        1, 0, 1, 1, 1, 0, 1, 1, 1,

                                        1, 0, 1, 1, 1, 1, 0, 0, 1, // back
                                        0, 0, 1, 1, 1, 1, 0, 1, 1,

                                        0, 0, 1, 0, 1, 1, 0, 0, 0, // left
                                        0, 0, 0, 0, 1, 1, 0, 1, 0,

                                        0, 0, 0, 1, 0, 0, 0, 0, 1, // bottom
                                        0, 0, 1, 1, 0, 0, 1, 0, 1,

                                        0, 1, 0, 0, 1, 1, 1, 1, 0, // top
                                        1, 1, 0, 0, 1, 1, 1, 1, 1};

float* createParticuleVerticesArray(state* particuleState){
    float *vertices = malloc(36 * 3 * sizeof(float));
    for(int i = 0; i < 108; i++){
        vertices[i] = particuleState->size * (verticesCubes[i] - 0.5);
    }

    return vertices;
}

static float distanceBetweenParticules(state* state1, state* state2){
    float deltaX = state1->position[0]-state2->position[0];
    float deltaY = state1->position[1]-state2->position[1];
    float deltaZ = state1->position[2]-state2->position[2];
    return (float)sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}

static float* vectorProduct(float vec1[3], float vec2[3]){
    float* result = malloc(3 * sizeof(float));
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
    return result;
}

static void checkCollision(state* state1, state* state2){
    float distance = distanceBetweenParticules(state1, state2);
    // if collision
    if(distance <= state1->size/2 + state2->size/2){
        // Determine collision space
        float collisionDirection[3] = { (state2->position[0] - state1->position[0])/distance, 
                                        (state2->position[1] - state1->position[1])/distance,
                                        (state2->position[2] - state1->position[2])/distance,};
        
        float normN = (float)sqrt(1 + collisionDirection[0] * collisionDirection[0] * (1/(collisionDirection[1] * collisionDirection[1])));
        float nVector[3] = {1/normN, -(collisionDirection[0]/collisionDirection[1])/normN, 0};

        float* zVector = vectorProduct(collisionDirection, nVector);

        //printf("g : %f %f %f\n", collisionDirection[0], collisionDirection[1], collisionDirection[2]);
        //printf("n : %f %f %f\n", nVector[0], nVector[1], nVector[2]);
        //printf("z : %f %f %f\n", zVector[0], zVector[1], zVector[2]);

        // Express direction of particules in collision space
        vec3 oldDirection1CollisionSpace = {state1->direction[0] * collisionDirection[0] + state1->direction[1] * nVector[0] + state1->direction[2] * zVector[0],
                                            state1->direction[0] * collisionDirection[1] + state1->direction[1] * nVector[1] + state1->direction[2] * zVector[1],
                                            state1->direction[0] * collisionDirection[2] + state1->direction[1] * nVector[2] + state1->direction[2] * zVector[2]};

        vec3 oldDirection2CollisionSpace = {state2->direction[0] * collisionDirection[0] + state2->direction[1] * nVector[0] + state2->direction[2] * zVector[0],
                                            state2->direction[0] * collisionDirection[1] + state2->direction[1] * nVector[1] + state2->direction[2] * zVector[1],
                                            state2->direction[0] * collisionDirection[2] + state2->direction[1] * nVector[2] + state2->direction[2] * zVector[2]};

        //printf("CS1 : %f %f %f\n", oldDirection1CollisionSpace[0], oldDirection1CollisionSpace[1], oldDirection1CollisionSpace[2]);
        //printf("CS2 : %f %f %f\n", oldDirection2CollisionSpace[0], oldDirection2CollisionSpace[1], oldDirection2CollisionSpace[2]);

        vec3 newDirection1CollisionSpace = {oldDirection2CollisionSpace[0], oldDirection1CollisionSpace[1], oldDirection1CollisionSpace[2]};
        vec3 newDirection2CollisionSpace = {oldDirection1CollisionSpace[0], oldDirection2CollisionSpace[1], oldDirection2CollisionSpace[2]};

        // Determine how to switch from collision space to normal space
        mat3 collisionSpace;
        glm_mat3_identity(collisionSpace);
        collisionSpace[0][0] = collisionDirection[0];
        collisionSpace[0][1] = collisionDirection[1];
        collisionSpace[0][2] = collisionDirection[2];
        collisionSpace[1][0] = nVector[0];
        collisionSpace[1][1] = nVector[1];
        collisionSpace[1][2] = nVector[2];
        collisionSpace[2][0] = zVector[0];
        collisionSpace[2][1] = zVector[1];
        collisionSpace[2][2] = zVector[2];


        mat3 normalSpace;
        glm_mat3_inv(collisionSpace, normalSpace);

        vec3 newDirection1;
        vec3 newDirection2;

        glm_mat3_mulv(normalSpace, newDirection1CollisionSpace, newDirection1);
        glm_mat3_mulv(normalSpace, newDirection2CollisionSpace, newDirection2);

        // update direction of movement
        //printf("old1 : %f %f %f\n", state1->direction[0], state1->direction[1], state1->direction[2]);
        //printf("old2 : %f %f %f\n", state2->direction[0], state2->direction[1], state2->direction[2]);
        state2->direction[0] = newDirection1[0];
        state2->direction[1] = newDirection1[1];
        state2->direction[2] = newDirection1[2];
        state1->direction[0] = newDirection2[0];
        state1->direction[1] = newDirection2[1];
        state1->direction[2] = newDirection2[2];

        state1->position[0] += 0.001 * state1->direction[0];
        state1->position[1] += 0.001 * state1->direction[1];
        state1->position[2] += 0.001 * state1->direction[2];
        state2->position[0] += 0.001 * state2->direction[0];
        state2->position[1] += 0.001 * state2->direction[1];
        state2->position[2] += 0.001 * state2->direction[2];

        //printf("new : %f %f %f\n", state1->direction[0], state1->direction[1], state1->direction[2]);
        //printf("new2 : %f %f %f\n", state2->direction[0], state2->direction[1], state2->direction[2]);
        //printf("#############################\n\n");


        free(zVector);
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

    if(state->position[2] < -1){
        state->direction[2] *= -1;
    }

    if(state->position[2] > 1){
        state->direction[2] *= -1;
    }
}

void checkAllBoundaries(state** allParticulesStates, int nbrOfParticules){
    for(int i = 0; i < nbrOfParticules; i++){
        checkBoundaries(allParticulesStates[i]);
    }
}