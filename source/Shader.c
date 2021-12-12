#include "header/Shader.h"

#define MAX_CHAR_IN_LINE 512
#define MAX_NUMBER_OF_LINE 256

char* readVertexShader(const char* shaderName, int* shaderLength){
    char filename[100]; 
    FILE *vertexFile = NULL;
    char fileLine[MAX_CHAR_IN_LINE];
    char vertexShader[MAX_NUMBER_OF_LINE * MAX_CHAR_IN_LINE];
    int nbrCharVertexShader = 0;
    char* returnVertexShader = NULL;

    // Creating filename
    strcpy(filename, "./shaders/");
    strcat(filename, shaderName);
    strcat(filename, "_vs.glsl");


    // opening file
    vertexFile = fopen(filename, "r");

    if (vertexFile == NULL)
    {
        consolePrintError(strcat("Error when opening vertex file : ", shaderName));
        exit(-1);
    }

    // Reading file
    strcpy(vertexShader, ""); // Reinitializing strcat
    while (fgets(fileLine, MAX_CHAR_IN_LINE, vertexFile) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
    {
        strcat(vertexShader, fileLine);
        nbrCharVertexShader += (int)(strchr(fileLine, '\n') - fileLine) + 1;
    }

    // closing file
    fclose(vertexFile);

    // Copying vertexShader into returnVertexShader that will be returned
    printf("File contains %d char\n", nbrCharVertexShader);
    returnVertexShader = malloc(nbrCharVertexShader + 1);
    memcpy(returnVertexShader, vertexShader, nbrCharVertexShader);

    *shaderLength = nbrCharVertexShader;
    return returnVertexShader;
}

char* readFragmentShader(const char* shaderName, int* shaderLength){
    char filename[100]; 
    FILE *fragmentFile = NULL;
    char fileLine[MAX_CHAR_IN_LINE];
    char fragmentShader[MAX_NUMBER_OF_LINE * MAX_CHAR_IN_LINE];
    int nbrCharFragmentShader = 0;
    char* returnFragmentShader = NULL;

    // Creating filename
    strcpy(filename, "./shaders/");
    strcat(filename, shaderName);
    strcat(filename, "_fs.glsl");


    // opening file
    fragmentFile = fopen(filename, "r");

    if (fragmentFile == NULL)
    {
        consolePrintError(strcat("Error when opening fragment file : ", shaderName));
        exit(-1);
    }

    // Reading file
    strcpy(fragmentShader, ""); // Reinitializing strcat
    while (fgets(fileLine, MAX_CHAR_IN_LINE, fragmentFile) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
    {
        strcat(fragmentShader, fileLine);
        nbrCharFragmentShader += (int)(strchr(fileLine, '\n') - fileLine) + 1;
    }

    // closing file
    fclose(fragmentFile);

    // Copying vertexShader into returnVertexShader that will be returned
    printf("File contains %d char\n", nbrCharFragmentShader);
    returnFragmentShader = malloc(nbrCharFragmentShader + 1);
    memcpy(returnFragmentShader, fragmentShader, nbrCharFragmentShader);


    *shaderLength = nbrCharFragmentShader;
    return returnFragmentShader;
}


GLuint compileVertexShader(const char* shaderName){
    GLuint shaderID;
    int vertexLength = 0;
    char* vertexShader = NULL;

    consolePrintInformation("Compiling Vertex shader");

    shaderID = glCreateShader(GL_VERTEX_SHADER);
    vertexShader = readVertexShader(shaderName, &vertexLength);

    glShaderSource(shaderID, 1, &vertexShader, NULL);
    glCompileShader(shaderID);

    // Check if there is no error in the shader
    GLint compileStatus = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        consolePrintError("Could not compile vertex shader!");

        char errorMessage[500];
        glGetShaderInfoLog(shaderID, 500, NULL, errorMessage);
        consolePrintInformation(errorMessage);
        exit(-1);
    }

    consolePrintInformation("Correctly compiling vertex shader");

    free(vertexShader);

    // return ID
    return shaderID;
}


GLuint compileFragmentShader(const char* shaderName){
    GLuint shaderID = 0; 
    int fragmentLength = 0;
    char* fragmentShader = NULL;
    
    consolePrintInformation("Compiling fragment shader");

    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader = readFragmentShader(shaderName, &fragmentLength);

    glShaderSource(shaderID, 1, &fragmentShader, NULL);
    glCompileShader(shaderID);

    // Check if there is no error in the shader
    GLint compileStatus = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        consolePrintError("Could not compile fragment shader!");

        char errorMessage[500];
        glGetShaderInfoLog(shaderID, 500, NULL, errorMessage);
        consolePrintInformation(errorMessage);
        exit(-1);
    }

    consolePrintInformation("Correctly compiling fragment shader");

    free(fragmentShader);
    
    // return ID
    return shaderID;
}

GLuint compileShader(const char* shaderName){
    GLuint programID;
    GLuint vertexID;
    GLuint fragmentID;

    programID = glCreateProgram();

    // Compile Fragment shader
    fragmentID = compileFragmentShader(shaderName);

    // Compile Vertex shader
    vertexID = compileVertexShader(shaderName);


    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);
    glValidateProgram(programID);

    // Check if there is no error in the shader
    GLint compileStatus = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        consolePrintError("Could not compile shader!");

        char errorMessage[500];
        glGetShaderInfoLog(programID, 500, NULL, errorMessage);
        consolePrintInformation(errorMessage);
        exit(-1);
    }

    consolePrintInformation("Correctly compiling shader");

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return programID;
}