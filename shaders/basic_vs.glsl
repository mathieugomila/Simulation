#version 330 core
layout (location = 0) in vec3 pos;

uniform vec3 particulePosition;
uniform mat4 perspMatrix;

out vec4 color_fs;
out vec3 position_fs;

void main(){
    gl_Position = perspMatrix * vec4(pos + particulePosition + vec3(0, 0, -3), 1);
    color_fs = vec4(0.5 * (particulePosition + vec3(1, 1, 1)), 1);
    position_fs = pos;
}
