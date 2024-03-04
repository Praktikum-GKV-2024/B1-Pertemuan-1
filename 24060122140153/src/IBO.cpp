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
    GLuint colorbuffer;
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
             0.3f,  0.0f, //0 A1
             0.0f, -0.3f, //1 A2
            -0.3f,  0.0f, //2 A3
             0.0f,  0.3f, //3 A4
            -0.5f,  0.0f, //4 A7
             0.0f,  0.5f, //5 A8
             0.5f,  0.0f, //6 A5
             0.0f, -0.5f, //7 A6
             0.0f, -0.8f, //8 A10
             0.8f,  0.0f, //9 A9
             0.0f,  0.8f, //10 A12
            -0.8f,  0.0f, //11 A11
             0.0f,  0.0f //12 A0
             
        };
        float g_color_buffer_data[] = {
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,  
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f
        };


        unsigned int indices[] = {
            0, 1, 12,
            1, 2, 12,//a1,a2,a3
            2, 3, 12,
            3, 0, 12,
            3, 5, 4,//a4,a8,a7
            0, 5, 3,//a1,a8,a4
            0, 6, 5,//a1,a5,a6
            0, 1, 6,//a1,a2,a5
            1, 7, 6,//a2,a6,a5
            1, 7, 2,//a2,a6,a3
            2, 4, 3, //a3,a7,a4
            2, 4, 7,//a3,a7,a6
            4, 8, 7,//a7,a10,a6
            7, 9, 8,//a6,a9,a10
            5, 10, 6, //A8,A12,a5
            10, 6, 9,//a12,a5,a9
            9, 6, 7,//a9,a5,a6
            10, 11, 5,//a12,a11,a8
            11, 4, 5,//a11,a7,a8
            11, 8, 4//a11,a10,a7

        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 2 * 20 * sizeof(float), positions, GL_STATIC_DRAW);

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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 20 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


        glGenBuffers(1, &colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, 13 * 3 * sizeof(float), g_color_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            0
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

        glDrawElements(GL_TRIANGLES, 62, GL_UNSIGNED_INT, nullptr);


        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};