#define GLM_FORCE_PURE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <iostream>
#include <common/shader.hpp>

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    GLLogCall(#x, _FILE, __LINE_)

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

static void GLLogCall(const char *function_name, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "Triggered Error Code: " << error << " at function call " << function_name << ", at " << file << ":" << line << std::endl;
    }
}

class MainScene
{
public:
    GLFWwindow *window;
    GLuint vao;
    GLuint buffer;
    GLuint ibo;
    GLuint programId;

    MainScene(GLFWwindow *window)
    {
        this->window = window;

        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // Cull triangles which normal is not towards the camera
        // glEnable(GL_CULL_FACE);

        start();
    }

    void start()
    {
        programId = LoadShaders("res/shader/super_basic.vs", "res/shader/super_basic.fs");

        // vertices to pass to GPU
        float positions[] = {
            0.f, 0.f, 1.0, 1.0, 1.0,   // A0 - White
            0.3f, 0.f, 1.0, 0.0, 0.0,  // A1 - Red
            0.f, -0.3f, 1.0, 0.0, 0.0, // A2 - Red
            -0.3f, 0.f, 1.0, 0.0, 0.0, // A3 - Red
            0.f, 0.3f, 1.0, 0.0, 0.0,  // A4 - Red
            0.5f, 0.f, 0.0, 1.0, 0.0,  // A5 - Green
            0.f, -0.5f, 0.0, 1.0, 0.0, // A6 - Green
            -0.5f, 0.f, 0.0, 1.0, 0.0, // A7 - Green
            0.f, 0.5f, 0.0, 1.0, 0.0,  // A8 - Green
            0.8f, 0.f, 0.0, 0.0, 1.0,  // A9 - Blue
            0.f, -0.8f, 0.0, 0.0, 1.0, // A10 - Blue
            -0.8f, 0.f, 0.0, 0.0, 1.0, // A11 - Blue
            0.f, 0.8f, 0.0, 0.0, 1.0   // A12 - Blue
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 1, 4,
            1, 5, 8,
            1, 5, 2,
            2, 5, 6,
            2, 6, 3,
            3, 7, 6,
            3, 7, 4,
            4, 7, 8,
            1, 4, 8,
            5, 12, 9,
            5, 9, 6,
            6, 9, 10,
            6, 7, 10,
            7, 10, 11,
            7, 8, 11,
            8, 11, 12,
            8, 5, 12

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
            0,                 // index for layout VAO
            2,                 // vector size of data type
            GL_FLOAT,          // data type
            GL_FALSE,          // normalized? map to 0 - 255
            5 * sizeof(float), // gaps
            0                  // offset
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                          // index untuk layout VAO
            3,                          // vector size of data type
            GL_FLOAT,                   // data type
            GL_FALSE,                   // normalized?
            5 * sizeof(float),          // gaps
            (void *)(2 * sizeof(float)) // offset
        );

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 20 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void update()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // do every frame here
        glUseProgram(programId);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLES, 20 * 3, GL_UNSIGNED_INT, nullptr);
    }
};
