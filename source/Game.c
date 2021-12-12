#include "header/Game.h"

int gameSetup(window_t* window){
    // Initialisating glfw and settings up some parameters
    consolePrintInformation("Initialization GLFW and GLEW");

    if(!glfwInit()){
        consolePrintError("Can't initialize glfw");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Because we are using opengl 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating the window and checking if the windows has been correctly created
    window->ID = glfwCreateWindow(window->width, window->height, "Learn OpenGL", NULL, NULL);

    if(window->ID == NULL){
        consolePrintError("Can't create glfw window");
        glfwTerminate();
        return -1; // There has been an error
    }

    // Specify which window to use and setting viewport
    glfwMakeContextCurrent(window->ID);
    glViewport(0, 0, window->width, window->height);

    // Setting up glew (opengl)
    if(glewInit() != GLEW_OK){
        consolePrintError("Can't initialize glew");
        return -1;
    }
    // Setup ended correctly
    return 0;
}

int gameLoadContent(){
    // Create array of point

    // Load shader
    GLuint programID = compileShader("basic");

    return 0;
}

int gameUpdate(window_t* window){

    // Update input (keyboard/mouse) data
    glfwPollEvents();

    if(glfwWindowShouldClose(window->ID) || glfwGetKey(window->ID, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        return 1;
    }

    return 0;
}
int gameDraw(){
    return 0;
}
int gameTerminate(){
    glfwTerminate();
    return 0;
}