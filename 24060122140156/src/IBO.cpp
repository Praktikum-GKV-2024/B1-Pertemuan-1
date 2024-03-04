#define GLM_FORCE_PURE

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
#include <common/loader.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>

#define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__)

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}
static void GLLogCall(const char* function_name, const char* file, int line) {
    while (GLenum error = glGetError()) {
        cout << "Triggered Error Code: " << error << " at function call " << function_name << ", at " << file << ":" << line << std::endl;
    }
}

class MainScene {
public:
    GLFWwindow* window;
    GLuint vao;
    GLuint buffer;
    GLuint ibo;
    GLuint programId;

    MainScene (GLFWwindow* window) {
        this->window = window;

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS); 

        // Cull triangles which normal is not towards the camera
        // glEnable(GL_CULL_FACE);

        start();
    }

    void start() {
        programId = LoadShaders("res/shader/super_basic.vs", "res/shader/super_basic.fs");

        // vertecies yang di pass ke GPU
        float positions[] = {
            0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 0

            0.3f,  0.0f, 1.0f, 0.0f, 0.0f, // 1
            0.0f,  -0.3f, 1.0f, 0.0f, 0.0f, // 2
            -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 3
            0.0f,  0.3f, 1.0f, 0.0f, 0.0f, // 4

            0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // 5
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, // 6
            -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // 7
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, // 8

            0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 9
            0.0f, -0.8f, 0.0f, 0.0f, 1.0f, // 10
            -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 11
            0.0f, 0.8f, 0.0f, 0.0f, 1.0f, // 12
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 1,

            1, 2, 5,
            2, 5, 6,
            5, 6, 9,
            6, 9, 10,

            2, 3, 6,
            3, 6, 7,
            6, 7, 10,
            7, 10, 11,

            3, 4, 7,
            4, 7, 8,
            7, 8, 11,
            8, 11, 12,

            4, 1, 8,
            1, 8, 5, 
            8, 5, 12,
            5, 12, 9,
        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 5 * 13 * sizeof(float), positions, GL_STATIC_DRAW);

        // setting the layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, // index untuk layout VAO
            2, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            5 * sizeof(float), // gaps
            0                  // offset
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, // index untuk layout VAO
            3, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized?
            5 * sizeof(float), // gaps
            (void*)(2 * sizeof(float)) // offset
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 20 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void update() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /* do every frame here*/
        glUseProgram(programId);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, nullptr);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};