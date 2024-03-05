// #version 330 core

// // Output data sebuah warna
// layout(location = 0) out vec4 color;

// void main(){
// 	// Output color, warna yang akan digambar ke layar
// 	color = vec4(0.8, 0.8, 0.8, 1.);

// 	// vec3 green = vec3(0.0, 1.0, 0.0);
//     // vec3 red = vec3(1.0, 0.0, 0.0);
//     // vec3 finalColor = mix(green, red, gradient);

// 	// color = vec4(finalColor, 1.0);
// }

#version 330 core

in vec3 color; // Receive color from vertex shader

out vec4 FragColor;

void main() {
    FragColor = vec4(color, 1.0); // Set fragment color from the input
}