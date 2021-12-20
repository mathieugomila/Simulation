#version 330 core
out vec4 finalColor;
  
in vec4 color_fs;  
in vec3 position_fs;

void main()
{
    finalColor = color_fs;
}
