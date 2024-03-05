#pragma once

#define GLM_FORCE_PURE
// #include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <common/shader.hpp>
#include <common/loader.hpp>
#include <common/controls.hpp>

class Object {
public:
    GLuint Material;
    GLuint MatrixID;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    GLFWwindow* window;

    MainScene (GLFWwindow* window) {
        this->window = window;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.4f, 0.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS); 

        // Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);


        // Create and compile our GLSL program from the shaders
        Material = LoadShaders( "res/shader/basic.vsh", "res/shader/basic.fsh" );

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(Material, "MVP");

        // bool res = loadOBJ("res/SK_Spider_Tank_Exploder_A.obj", vertices, uvs, normals);
        bool res = loadOBJ("res/obj/cube.obj", vertices, uvs, normals);

        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    }

    void start() {

    }

    void update() {
    //    // Use our shader
	// 	glUseProgram(Material);

	// 	// Compute the MVP matrix from keyboard and mouse input
	// 	computeMatricesFromInputs(window);
	// 	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	// 	glm::mat4 ViewMatrix = getViewMatrix();
	// 	glm::mat4 ModelMatrix = glm::mat4(1.0);
	// 	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// 	// Send our transformation to the currently bound shader, 
	// 	// in the "MVP" uniform
	// 	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 	// 1rst attribute buffer : vertices
	// 	glEnableVertexAttribArray(0);
	// 	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 	glVertexAttribPointer(
	// 		0,                  // attribute
	// 		3,                  // size
	// 		GL_FLOAT,           // type
	// 		GL_FALSE,           // normalized?
	// 		0,                  // stride
	// 		(void*)0            // array buffer offset
	// 	);

	// 	// 2nd attribute buffer : UVs
	// 	glEnableVertexAttribArray(1);
	// 	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	// 	glVertexAttribPointer(
	// 		1,                                // attribute
	// 		2,                                // size
	// 		GL_FLOAT,                         // type
	// 		GL_FALSE,                         // normalized?
	// 		0,                                // stride
	// 		(void*)0                          // array buffer offset

	// 	);

	// 	// Draw the triangle !
	// 	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	// 	glDisableVertexAttribArray(0);
	// 	glDisableVertexAttribArray(1);
        glBegin(GL_TRIANGLES);
                glVertex2d(1, 1);
                glVertex2d(0, 0);
                glVertex2d(1, 0);
        glEnd();
    }
};