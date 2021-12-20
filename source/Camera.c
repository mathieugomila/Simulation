#include "header/Camera.h"


void updatePerspectiveCamera(GLuint shader){
    mat4 perspectiveMatrix;
    float fov = 90 * (3.1415/180);
    glm_perspective(fov, 1, 0.001, 10, perspectiveMatrix);
    //glm_ortho(-1, 1, -1, 1, 0, 10, perspectiveMatrix);

    sendUniformValue4x4(shader, "perspMatrix", perspectiveMatrix);
}