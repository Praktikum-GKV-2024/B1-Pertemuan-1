#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

void main(){
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = position;
	fragmentColor = vertexColor;
}