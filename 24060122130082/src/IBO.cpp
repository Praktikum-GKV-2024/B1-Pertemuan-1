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

        glClearColor(1.0f, 1.0f, 1.4f, 1.0f);

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
            /*coordinate*/      /*color*/
            -0.15f, 0.75f,      1.0f, 0.5f, 0.0f,   /*0*/   /*KEPALA RUBAH*/
            -0.44f, 0.96f,      1.0f, 0.5f, 0.0f,   /*1*/
            -0.39f, 0.58f,      1.0f, 0.5f, 0.0f,   /*2*/
            -0.05f,  0.3f,      1.0f, 0.5f, 0.0f,   /*3*/   
             -0.5f, 0.28f,      1.0f, 0.5f, 0.0f,   /*4*/   
            -0.22f, 0.44f,      1.0f, 0.5f, 0.0f,   /*5*/   
            -0.06f, 0.12f,      1.0f, 0.5f, 0.0f,   /*6*/   
              0.0f,  0.0f,      1.0f, 1.0f, 1.0f,   /*7*/   
             0.15f, 0.75f,      1.0f, 0.5f, 0.0f,   /*8*/   
             0.44f, 0.96f,      1.0f, 0.5f, 0.0f,   /*9*/   
             0.39f, 0.58f,      1.0f, 0.5f, 0.0f,   /*10*/    
             0.05f,  0.3f,      1.0f, 0.5f, 0.0f,   /*11*/    
              0.5f, 0.28f,      1.0f, 0.5f, 0.0f,   /*12*/    
             0.22f, 0.44f,      1.0f, 0.5f, 0.0f,   /*13*/    
             0.06f, 0.12f,      1.0f, 0.5f, 0.0f,    /*14*/

            -0.25f, 0.14f,      1.0f, 0.5f, 0.0f,   /*15*/
              0.0f, -0.4f,      1.0f, 0.5f, 0.0f,   /*16*/
             0.25f, 0.14f,      1.0f, 0.5f, 0.0f,   /*17*/
              0.6f,  0.0f,      1.0f, 0.5f, 0.0f,   /*18*/
              0.0f, -0.8f,      1.0f, 0.5f, 0.0f,   /*19*/
            -0.55f, -0.7f,      1.0f, 0.5f, 0.0f,   /*20*/
             -0.8f, -0.4f,      1.0f, 0.5f, 0.0f,   /*21*/
              0.3f, -0.6f,      1.0f, 0.5f, 0.0f,   /*22*/

        };

        unsigned int indices[] = {
            0, 1, 2,    // segitiga 1   KEPALA RUBAH
            2, 3, 0,    // segitiga 2
            
            5, 2, 4,    // Segitiga 3
            4, 6, 5,    // Segitiga 4

            3, 5, 7,     // Segitiga 5

            8, 9, 10,   // segitiga 1
            10, 11, 8,  // segitiga 2
            
            13, 10, 12, // Segitiga 3
            12, 14, 13, // Segitiga 4

            11, 13, 7,   // Segitiga 5

            0, 7, 8,     //segitiga 11

            6, 15, 16,
            16, 17, 14


        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 23 * 5 * sizeof(float), positions, GL_STATIC_DRAW);

        // setting the layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, // index untuk layout VAO
            2, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            5 * sizeof(float), // stride (size of vertex)
            0 //offset 
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, // index untuk layout VAO
            3, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized? map to 0 - 255
            5 * sizeof(float), // stride (size of vertex)
            (void*)(2 * sizeof(float)) // offset (colors, after positions)
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 13 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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

        glDrawElements(GL_TRIANGLES, 13 * 3, GL_UNSIGNED_INT, nullptr);
    

        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};