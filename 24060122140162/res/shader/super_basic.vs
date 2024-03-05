#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 ourColor;

void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = position;
    ourColor = color;
}