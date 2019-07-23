#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to load glew\n");
    }

    const GLchar *vert_shader =
        "#version 330\n"
        "layout(location = 0) in vec4 position;\n"
        "void main() {\n"
        "   gl_Position = position;"
        "}";

    GLuint vao;

    float positions[] {
        0.5, 0.5,
        -0.5, 0.5,
        -0.5, 0.5,
    }

    unsigned int vertexarray;
    glGenVertexArrays(1, &vertexarray);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}