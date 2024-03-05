#version 330 core

// in vec4 position;

// Output data
layout(location = 0) out vec4 color;

in vec3 ourColor;
in vec4 gl_FragCoord;

void main(){

    // Output color = color of the texture at the specified UV
    // color = vec4(gl_FragCoord.x / 640., gl_FragCoord.x / 480., 0., 0. ); //vec4(1., 0., 0., 1.);
    color = vec4(ourColor, 1.);
    // color = vec4(gl_FrontFacing, gl_FrontFacing, gl_FrontFacing, gl_FrontFacing);
}