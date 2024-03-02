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
        // glDepthFunc(GL_LESS); 

        // Cull triangles which normal is not towards the camera
        // glEnable(GL_CULL_FACE);

        start();
    }

    void start() {
        programId = LoadShaders("res/shader/super_basic.vs", "res/shader/super_basic.fs");

        // vertecies yang di pass ke GPU
        float positions[] = {
            0,      0,    255/255., 255./255., 255./255., // 0

            // 0,      1,    246/255., 136/255., 111/255., // 1
            // 0.866,  -0.5, 161/255., 229/255., 230/255., // 2
            // -0.866, -0.5, 50/255.,   23/255., 100/255., // 3

            // 0,      -1,   205/255., 154/255., 221/255., // 4
            // 0.866,  0.5,  189/255., 249/255., 177/255., // 5
            // -0.866, 0.5,  224/255., 142/255., 148/255., // 6

            // 0,      0.5, 255/255., 255./255., 255./255., //
            // -0.288, 0.5, 255/255., 255./255., 255./255.,
            // 0.288,  0.5, 255/255., 255./255., 255./255.,

            // -0.288,-0.5, 255/255., 255./255., 255./255.,
            // 0.288, -0.5, 255/255., 255./255., 255./255.,

            // 4.2,  -0.25, 255/255., 255./255., 255./255.,
            // -4.2, -0.25, 255/255., 255./255., 255./255.,

            // 0.3f, 0.5f, //0
            // 0.5f, 0.0f, //1
            // 0.3f, -0.5f, //2
            // -0.3f, -0.5f, //3
            // -0.5f, 0.0f, //4
            // -0.3f, 0.5f,  //5

            -0.2, 0.3, 225/255., 198/255., 132/255.,
            -0.4, 0.0, 199/255., 56/255., 110/255.,
            -0.6, 0.3, 250/255., 189/255., 192/255.,

            -0.2, -0.3, 113/255., 23/255., 137/255.,
            0.2, -0.3,  177/255., 234/255., 238/255.,
            0.2, 0.3,   147/255., 241/255., 148/255.,
            0.4, 0,     43/255., 156/255., 138/255.,
            0, 0.6,     252/255., 167/255., 143/255.,
            -0.6, -0.3, 70/255., 43/255., 118/255.,
            0, -0.6,    129/255., 66/255., 218/255.,
            0.6, 0.3,   121/255., 225/255., 108/255.,
            0.6, -0.3,  158/255., 232/255., 233/255.,

            // -0.2, 0.3, 1, 1, 1,
            // -0.4, 0.0, 1, 1, 1,

        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 4,
            0, 4, 5,
            0, 5, 7,
            0, 6, 7,
            0, 1, 6,

            4, 5, 10,
            5, 7, 12,
            6, 7, 11,
            1, 6, 8,
            1, 2, 3,
            2, 4, 9,

            // 0, 13, 14
        };

        // Initialize Vertex Array Buffer
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // setup vertex buffers
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, (2 + 3) * 13 * sizeof(float), positions, GL_STATIC_DRAW);

        // setting the layout
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, // index untuk layout VAO
            2, // vector size of data type
            GL_FLOAT, // data type
            GL_FALSE, // normalized?
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
            (void*)(2* sizeof(float)) // offset
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

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

        glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr);


        // glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};
