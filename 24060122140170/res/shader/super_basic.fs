#version 330 core

in vec3 color; // Receive color from vertex shader

out vec4 FragColor;

void main() {
    FragColor = vec4(color, 1.0); // Set fragment color from the input
}
