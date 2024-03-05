//Nama : Abdul Majid
//NIM  : 24060122120035

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

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
           0.0f , 0.0f, //A0
           0.3f , 0.0f, //A1
           0.0f , -0.3f,//A2
           -0.3f , 0.0f, //A3
           0.0f , 0.3f , //A4

           0.5f , 0.0f, //A5
           0.0f , -0.5f,//A6
           -0.5f , 0.0f, //A7
           0.0f , 0.5f , //A8

           0.8f , 0.0f, //A9
           0.0f , -0.8f,//A10
           -0.8f , 0.0f, //A11
           0.0f , 0.8f , //A12
        };
        float colors[] = {
            // atas
            1.0f, 1.0f, 1.0f, // putih

            1.0f, 0.0f, 0.0f, // merah
            1.0f, 0.0f, 0.0f, // merah
            1.0f, 0.0f, 0.0f, // merah
            1.0f, 0.0f, 0.0f, // merah

            // kiri bawah
            0.0f, 1.0f, 0.0f, // hijau
            0.0f, 1.0f, 0.0f, // hijau
            0.0f, 1.0f, 0.0f, // hijau
            0.0f, 1.0f, 0.0f, // hijau

            // kanan bawah
            0.0f, 0.0f, 1.0f, // biru
            0.0f, 0.0f, 1.0f, // biru
            0.0f, 0.0f, 1.0f,  // biru
            0.0f, 0.0f, 1.0f  // biru
        };


        unsigned int indices[] = {
            
            0,1,2,
            0,2,3,
            0,3,4,
            0,4,1,

            4,8,1,
            8,1,5,
            1,5,2,
            5,2,6,
            2,3,6,
            3,6,7,
            3,7,4,
            7,4,8,

            12,5,8,
            12,5,9,
            6,9,5,
            6,9,10,
            7,10,6,
            7,10,11,
            11,8,7,
            11,8,12
            
        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER,13*2* sizeof(float), positions, GL_STATIC_DRAW);

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
        // setup vertex buffers for color
        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, 13 * 3 * sizeof(float), colors, GL_STATIC_DRAW);

        // setting the layout for color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, // index untuk layout VAO
            3, // vector size of data type (RGB)
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 1
            3 * sizeof(float), // gaps
            0                  // offset
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

        glDrawElements(GL_TRIANGLES,20*3, GL_UNSIGNED_INT, nullptr);


        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};