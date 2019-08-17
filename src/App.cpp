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
    GLuint ebo;
    long frameCount;
    double lastFrame;
};

int main(void) {

    graphicsContext gc;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gc.window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
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

    GLfloat vertices[] {
         0.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    // GLushort elements[] = {
    //     0, 0, 1, 0, 2, 0,
    //     0, 1, 1, 1, 2, 1,
    //     0, 2, 1, 2, 2, 2,
    //     0, 2, 1, 2, 2, 2
    // };


    GLCall(glGenVertexArrays(1, &gc.vao));
    GLCall(glBindVertexArray(gc.vao));

    GLCall(glGenBuffers(1, &gc.vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, gc.vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 0, GL_STATIC_DRAW));
    GLCall(glNamedBufferSubData(gc.vbo, 0, sizeof(vertices), &vertices));


    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        NULL
    ));

    // GLCall(glGenBuffers(1, &gc.ebo));
    // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gc.ebo));
    // GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW));

    GLuint vertexShader = loadShader("./shaders/test.vertexShader", GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader("./shaders/first.fragmentShader", GL_FRAGMENT_SHADER);

    GLuint program = createProgram(vertexShader, fragmentShader);

    float angle = 0.01f;

    glm::mat4 model;
    glm::mat4 unmodel = glm::mat4(1.0f);
    // glm::mat4 view = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f, 0.1f, 100.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    GLCall(GLint s_model = glGetUniformLocation(program, "u_model"));
    GLCall(GLint s_view = glGetUniformLocation(program, "u_view"));
    GLCall(GLint s_projection = glGetUniformLocation(program, "u_projection"));

    unmodel = glm::scale(unmodel, glm::vec3(0.25f, 0.25f, 0.25f));

    GLCall(glClearColor(0.15f, 0.15f, 0.15f, 1.0f));

    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(gc.window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(program));

        GLCall(glBindVertexArray(gc.vao));

        GLCall(glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(view)));
        GLCall(glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(projection)));

        // GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void *)0));
        model = glm::translate(unmodel, glm::vec3(-1.0f, -1.0f, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        GLCall(glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        model = glm::translate(unmodel, glm::vec3(1.0f, -1.0f, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        GLCall(glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        model = glm::translate(unmodel, glm::vec3(-1.0f, 1.0f, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        GLCall(glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        model = glm::translate(unmodel, glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        GLCall(glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        /* Swap front and back buffers */
        glfwSwapBuffers(gc.window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}