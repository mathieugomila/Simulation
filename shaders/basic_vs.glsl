#version 330 core
layout (location = 0) in vec2 pos;

out vec4 color_fs;
out vec2 position_fs;

void main(){
    gl_Position = vec4(pos, 0, 1);
    color_fs = vec4(1, 1, 1, 1);
    position_fs = pos;
}
