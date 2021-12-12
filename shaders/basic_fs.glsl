#version 330 core
out vec4 finalColor;
  
in vec4 color_fs;  

void main()
{
    finalColor = color_fs;
}
