
#version 330 core
layout(location = 0) in vec2 aPos; // position attribute
layout(location = 1) in vec3 aColor; // color attribute

out vec3 color; // pass color to fragment shader

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    color = aColor; // pass color to fragment shader
}
