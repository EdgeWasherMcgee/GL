#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "common/renderer.h"
#include "common/shaderHandler.h"

struct graphicsContext {
    GLFWwindow *window;
    GLuint program;
    GLuint vbo;
    GLuint vao;
    long frameCount;
    double lastFrame;
};

int main(void) {

    graphicsContext gc;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    gc.window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!gc.window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(gc.window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to load glew\n");
    }

    GLfloat positions[] {
        0.0f, 0.0f,
        0.3f, -0.7f,
        -0.3f, -0.7f,
        0.0f, 0.0f,
        0.7f, -0.3f,
        0.7f, 0.3f,
        0.0f, 0.0f,
        0.3f, 0.7f,
        -0.3f, 0.7f,
        0.0f, 0.0f,
        -0.7f, -0.3f,
        -0.7f, 0.3f
    };

    GLCall(glGenVertexArrays(1, &gc.vao));
    GLCall(glBindVertexArray(gc.vao));

    GLCall(glGenBuffers(1, &gc.vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, gc.vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLuint vertexShader = loadShader("./shaders/first.vertexShader", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader("./shaders/first.fragmentShader", GL_FRAGMENT_SHADER);

    GLuint program = createProgram(vertexShader, fragmentShader);

    GLCall(glClearColor(0.15f, 0.15f, 0.15f, 1.0f));

    GLCall(glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *)0
    ));

    float angle = 0.0f;

    GLCall(GLint s_angle = glGetUniformLocation(program, "theta"));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(gc.window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, gc.vbo));

        GLCall(glUseProgram(program));

        GLCall(glUniform1f(s_angle, angle));

        GLCall(glDrawArrays(GL_LINE_LOOP, 0, 12));
        GLCall(glDisableVertexAttribArray(0));

        /* Swap front and back buffers */
        glfwSwapBuffers(gc.window);

        /* Poll for and process events */
        glfwPollEvents();
        angle += 0.01;
    }

    glfwTerminate();
    return 0;
}