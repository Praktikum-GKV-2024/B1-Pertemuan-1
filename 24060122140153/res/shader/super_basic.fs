# version 330 core

// in vec4 position;
in vec3 fragmentColor;

// Output data
layout(location = 0) out vec4 color;
//layout(location = 1) out vec3 color1;

void main(){

	// Output color = color of the texture at the specified UV
	// color = vec4(gl_FragCoord., 0, 1); //vec4(1., 0., 0., 1.);
	color = vec4(fragmentColor, 1.);
}