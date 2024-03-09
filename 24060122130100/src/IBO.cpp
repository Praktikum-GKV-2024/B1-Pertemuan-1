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
    GLuint colorbuffer;

    MainScene (GLFWwindow* window) {
        this->window = window;

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
             0.0f,  0.0f, // 0 kuadran 1 diamond 1, titik tengah
             0.10f, 0.25f, // 1 kuadran 2 diamond 1
             0.0f, 1.0f, // 2 kuadran 3 diamond 1
            -0.10f, 0.25f, // 3 diamond 1
            0.0f, 0.0f,
             0.10f, -0.25f, // 5 diamond 2
             0.0f, -1.0f, // 6 diamond 2
             -0.10f, -0.25f, // 7 diamond 2
             0.0f, 0.0f,
             0.15f, 0.12f, // 9 diamond 3
             0.80f, 0.0f, // 10 diamond 3
             0.15f, -0.12f, // 11 diamond 3
             0.0f, 0.0f,
             -0.15, 0.12f, //13 diamond 4
             -0.80f, 0.0f, //14 diamond 4
             -0.15f, -0.12f, //15 diamond 4
             0.22f, 0.25f, // 16 triangle 1
             0.18f, 0.45f, // 17 triangle 1
             0.35f, 0.20f, // 18 triangle 1
             0.22f, -0.25f, // 19 triangle 2
             0.18f, -0.45f, //20 triangle 2
             0.35f, -0.20f, //21 triangle 2
             -0.22f, 0.25f, // 22 triangle 3
             -0.18f, 0.45f, //23 triangle 3
             -0.35f, 0.20f, //24 triangle 3
             -0.22f, -0.25f, // 25 triangle 4
             -0.18f, -0.45f, //26 triangle 4
             -0.35f, -0.20f, //27 triangle 4
             0.10f, 1.0f, //28
             0.80f, 0.15f, // 29
             0.40f, 0.50f, // 30
             0.10f, -1.0f, //31
             0.80f, -0.15f, // 32
             0.40f, -0.50f, // 33
             -0.10f, 1.0f, //34
             -0.80f, 0.15f, // 35
             -0.40f, 0.50f, // 36
             -0.10f, -1.0f, //37
             -0.80f, -0.15f, // 38
             -0.40f, -0.50f, // 39

        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            8, 9, 10,
            10, 11, 8,
            12, 13, 14,
            14, 15, 12,
            16, 17, 18,
            19, 20, 21,
            22, 23, 24,
            25, 26, 27,
            28, 29, 30,
            31, 32, 33,
            34, 35, 36,
            37, 38, 39
    
        };

        float colors[] = {
            1.0f, 0.85f, 0.0f,
            1.0f, 0.85f, 0.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 0.85f, 1.0f,
            1.0f, 0.85f, 1.0f,
            1.0f, 0.5f, 1.0f,
            1.0f, 0.5f, 1.0f,
            1.0f, 1.0f, 0.85f,
            1.0f, 1.0f, 0.85f,
            1.0f, 1.0f, 0.5f,
            1.0f, 1.0f, 0.5f,
            1.0f, 0.85f, 1.0f,
            1.0f, 0.85f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 0.0f, 0.5f,
            1.0f, 0.0f, 0.5f,
            1.0f, 0.0f, 0.5f,
            1.0f, 0.5f, 0.5f,
            1.0f, 0.5f, 0.5f,
            1.0f, 0.5f, 0.5f,
            1.0f, 0.5f, 0.75f,
            0.5f, 0.5f, 0.75f,
            0.5f, 0.5f, 0.75f,
            0.5f, 0.5f, 0.75f,
        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 40 * 2 * sizeof(float), positions, GL_STATIC_DRAW);


        // setting the layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, // index untuk layout VAO
            2, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            2 * sizeof(float), // gaps
            0                  // offset
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 16 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, 40 * 3 * sizeof(float), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            0                          // array buffer offset
        );

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

        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, nullptr);


        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }


};