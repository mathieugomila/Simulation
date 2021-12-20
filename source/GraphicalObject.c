#include "header/GraphicalObject.h"


GLuint createVAO2D(float* vertices, int nbrVertices){
    GLuint vaoID;
    GLuint vboID;

    // Create vao object and storing its id in vaoID[1]
    glGenVertexArrays(1, &vaoID);
    
    // Binding vao so that we can use it
    glBindVertexArray(vaoID);

    // same for vbo
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Defining the size of the array, the data and the type of vbo
    glBufferData(GL_ARRAY_BUFFER, nbrVertices * 2 * sizeof(float), vertices, GL_STATIC_DRAW); 
    
    // Give information about the attrib 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vaoID;
}

GLuint createVAO3D(float* vertices, int nbrVertices){
    GLuint vaoID;
    GLuint vboID;

    // Create vao object and storing its id in vaoID[1]
    glGenVertexArrays(1, &vaoID);
    
    // Binding vao so that we can use it
    glBindVertexArray(vaoID);

    // same for vbo
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Defining the size of the array, the data and the type of vbo
    glBufferData(GL_ARRAY_BUFFER, nbrVertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW); 
    
    // Give information about the attrib 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind vao and vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vaoID;
}


void drawVAO(GLuint vaoID, int nbrVertices){
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, nbrVertices);
    glBindVertexArray(0);
}