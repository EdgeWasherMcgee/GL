#include "common/renderer.h"
#include "shader/shader.h"
#include "objects/vertexBuffer.h"
#include "objects/indexBuffer.h"
#include "objects/vao.h"

struct windowContext {
    GLFWwindow* window;
    GLuint vao;
    GLuint vbo;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    
    windowContext context;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /* Create a windowed mode window and its OpenGL context */
    context.window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!context.window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(context.window);

    GLenum err = glewInit();

    if(GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSetFramebufferSizeCallback(context.window, framebuffer_size_callback);

    /* Make the window's context current */

    Shader shader("shader/first.vertexShader", "shader/first.fragmentShader");
    shader.use();

    float vertices[] = {
        -0.5f,  -0.5f, 0.0f,
         0.5f,  -0.5f, 0.0f,
         0.0f,   0.5f, 0.0f
    };

    IndexBuffer ibo;
    VertexBuffer vbo;

    vbo.bufferData(sizeof(float) * 9, (void *) vertices);

    VAO vao(ibo, vbo);
    
    vao.addAttribute(GL_FLOAT, 3);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(context.window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));

        shader.use();

        vao.drawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(context.window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}