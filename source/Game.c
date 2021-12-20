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

int gameLoadContent(GLuint* shader, float* vertices, GLuint* vaoID, state** allParticulesStates, int nbrOfParticules){
    // Load shader
    *shader = compileShader("basic");

    // Create particules    
    for(int i = 0; i < nbrOfParticules; i++){
        allParticulesStates[i] = createParticule();
        vertices = createParticuleVerticesArray(allParticulesStates[i]);
        vaoID[i] = createVAO3D(vertices, 36);
    }   

    
    return 0;
}

int gameUpdate(window_t* window, state** allParticulesStates, int nbrOfParticules){
    // Update input (keyboard/mouse) data
    glfwPollEvents();

    if(glfwWindowShouldClose(window->ID) || glfwGetKey(window->ID, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        return 1;
    }

    checkAllCollision(allParticulesStates, nbrOfParticules);

    checkAllBoundaries(allParticulesStates, nbrOfParticules);

    // Update position of all particules
    for(int i = 0; i < nbrOfParticules; i++){
        allParticulesStates[i]->position[0] += 0.005 * allParticulesStates[i]->direction[0];
        allParticulesStates[i]->position[1] += 0.005 * allParticulesStates[i]->direction[1];
        allParticulesStates[i]->position[2] += 0.005 * allParticulesStates[i]->direction[2];
    }

    return 0;
}

int gameDraw(window_t* window, GLuint* shader, GLuint* vaoID, float* color, state** allParticulesStates, int nbrOfParticules){
    // Set up some parameters
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    // Reset different buffers
    glClearColor(*color, *color, *color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // draw using shader
    useShader(*shader);

    // Send position of the camera
    updatePerspectiveCamera(*shader);

    // update particule position    
    for(int i = 0; i < nbrOfParticules; i++){
        sendUniformValue3f(*shader, "particulePosition", allParticulesStates[i]->position);
        drawVAO(vaoID[i], 36);
    }

    // Stop using shader
    useShader(0);
    
    // swap buffers
    glfwSwapBuffers(window->ID);

    return 0;
}

int gameTerminate(){
    glfwTerminate();
    return 0;
}