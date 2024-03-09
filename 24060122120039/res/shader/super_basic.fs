#version 330 core

// Input data dari vertex shader
in vec3 fragmentColor;

// Output warna
layout(location = 0) out vec4 color1;

void main(){
  color1 = vec4(fragmentColor, 1.);
}
