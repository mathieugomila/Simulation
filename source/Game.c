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

int gameLoadContent(GLuint* shader, float* vertices, GLuint* vaoID){
    // Load shader
    *shader = compileShader("basic");

    // Create array of point
    vertices = (float*)malloc(6 * 2 * sizeof(float));
    vertices[0] = 0;
    vertices[1] = 1.0;
    vertices[2] = 1.0;
    vertices[3] = 1.0;
    vertices[4] = 0;
    vertices[5] = 0;
    vertices[6] = 0;
    vertices[7] = 0;
    vertices[8] = 1.0;
    vertices[9] = 1.0;
    vertices[10] = 1.0;
    vertices[11] = 0;

    *vaoID = createVAO(vertices, 6);
    
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

int gameDraw(window_t* window, GLuint* shader, GLuint* vaoID){
    // Set up some parameters
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    //glFrontFace(GL_CW);

    // Reset different buffers
    glClearColor(0.5, 0.5, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // draw using shader
    useShader(*shader);
    drawVAO(*vaoID, 6);
    useShader(0);
    
    // swap buffers
    glfwSwapBuffers(window->ID);

    return 0;
}

int gameTerminate(){
    glfwTerminate();
    return 0;
}