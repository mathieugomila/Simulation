#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <time.h>


// Include other file of the project
#include "header/Console.h"
#include "header/Game.h"
#include "header/Particules.h"

int main(){
    int gameShouldContinue = 1; // True
    window_t window = {NULL, 1000, 1000};
    GLuint shader;
    float* vertices = NULL; 
    float color = 0.5;

    // Reset random
    srand(time(NULL));

    // Particules
    unsigned int nbrParticules = 100;
    state** allParticulesStates = malloc(nbrParticules * sizeof(state));
    GLuint* vaoID = malloc(nbrParticules * sizeof(GLuint));

    consolePrintInformation("Beginning of the simulation");

    consolePrintSection("SETUP");
    if(gameSetup(&window) == -1){
        consolePrintSection("Error while setting up");
        return -1;
    }

    consolePrintSection("LOAD CONTENT");
    if(gameLoadContent(&shader, vertices, vaoID, allParticulesStates, nbrParticules) == -1){
        consolePrintError("Error while loeading contents");
        return -1;
    }

    consolePrintSection("GAME LOOP");
    while(gameShouldContinue){
        if(gameUpdate(&window, allParticulesStates, nbrParticules)){
            consolePrintInformation("Request to stop the game");
            gameShouldContinue = 0;
        }
        else{
            if(gameDraw(&window, &shader, vaoID, &color, allParticulesStates, nbrParticules)){
                consolePrintError("Error while trying to draw");
                return -1;
            }
    	}
    }
    consolePrintSection("TERMINATE");
    free(vertices);
    return gameTerminate();
}


/*
TODO :
initialiser toutes les particules a des endroits random et des directions random

Regarder si collision et eventuellement modifier direction

*/