#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Include other file of the project
#include "header/Console.h"
#include "header/Game.h"

int main(){
    int gameShouldContinue = 1; // True
    window_t window = {NULL, 1000, 1000};
    GLuint shader;
    float* vertices = NULL; 
    GLuint vaoID;
    float color = 0.5;

    consolePrintInformation("Beginning of the simulation");

    consolePrintSection("SETUP");
    if(gameSetup(&window) == -1){
        consolePrintSection("Error while setting up");
        return -1;
    }

    consolePrintSection("LOAD CONTENT");
    if(gameLoadContent(&shader, vertices, &vaoID) == -1){
        consolePrintError("Error while loeading contents");
        return -1;
    }

    consolePrintSection("GAME LOOP");
    while(gameShouldContinue){
        if(gameUpdate(&window)){
            consolePrintInformation("Request to stop the game");
            gameShouldContinue = 0;
        }
        else{
            if(gameDraw(&window, &shader, &vaoID, &color)){
                consolePrintError("Error while trying to draw");
                return -1;
            }
    	}
    }
    consolePrintSection("TERMINATE");
    free(vertices);
    return gameTerminate();
}