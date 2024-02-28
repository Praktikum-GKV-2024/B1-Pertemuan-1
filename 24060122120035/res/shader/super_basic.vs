#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;

void main(){
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = position;
}