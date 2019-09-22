#include "common/renderer.h"
#include "shader/shader.h"
#include "objects/vertexBuffer.h"
#include "objects/indexBuffer.h"
#include "objects/vao.h"
#include "camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, width*0.625f);
}

int main(void) {
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    // const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /* Create a windowed mode window and its OpenGL context */
    // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Rotating square", monitor, NULL);
    GLFWwindow* window = glfwCreateWindow(1000, 600, "Rotating cube", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glViewport(0, 0, mode->width, mode->height);
    glViewport(0, 0, 1000, 600);

    /* Make the window's context current */

    Shader shader("shader/first.vertexShader", "shader/first.fragmentShader");
    shader.use();

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_FRAMEBUFFER_SRGB));
    // GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // float vertices[] = {

    //     -1.0f, -1.0f, -1.0f, 1.000f, 1.000f, 0.000f, //Front left down 0
    //     -1.0f,  1.0f, -1.0f, 0.000f, 1.000f, 0.000f, //Front right down 1
    //     -1.0f, -1.0f,  1.0f, 1.000f, 1.000f, 1.000f, //Front left up 2
    //     -1.0f,  1.0f,  1.0f, 0.000f, 1.000f, 1.000f, //Front right up 3
    //      1.0f, -1.0f, -1.0f, 1.000f, 0.000f, 0.000f, //Back left down 4
    //      1.0f,  1.0f, -1.0f, 0.000f, 0.000f, 0.000f, //Back right down 5
    //      1.0f, -1.0f,  1.0f, 1.000f, 0.000f, 1.000f, //Back left up 6
    //      1.0f,  1.0f,  1.0f, 0.000f, 0.000f, 1.000f, //Back right up 7
    // };

    unsigned short indices[] = {

        0, 1, 2,
        3, 2, 1,
        
        1, 5, 3,
        5, 3, 7,
        
        7, 6, 5,
        4, 5, 6,
        
        0, 4, 2,
        4, 2, 6,
        
        2, 3, 6,
        7, 6, 3,
        
        0, 1, 4,
        1, 4, 5,

    };

    Camera cam;
    VertexArray VAO;

    VAO.VBO.bufferData(sizeof(vertices), (void *) vertices);
    // VAO.IBO.bufferData(sizeof(indices), indices);

    GLuint indexCount = sizeof(indices)/sizeof(unsigned short);

    VAO.addAttribute(GL_FLOAT, 3);
    VAO.addAttribute(GL_FLOAT, 2);

    glm::mat4 u_modelMatrix(1);

    u_modelMatrix[3][0] = 0.5f;
    u_modelMatrix[3][1] = -0.5f;

    cam.setPos(glm::vec3(-10.0f, 0.0f, 0.0f));
    printMatrix(u_modelMatrix);
    printMatrix(cam.getViewMatrix());
    printMatrix(cam.getPerspectiveMatrix());
    printMatrix(cam.getPerspectiveMatrix() * cam.getViewMatrix() * u_modelMatrix);

    // modelMatrix = glm::rotate(modelMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // printf("%fms, %f fps\n", deltaTime, (1/deltaTime));


        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));

        shader.setUniform("matrix", u_modelMatrix * cam.getViewMatrix() * cam.getPerspectiveMatrix());

        shader.use();

        VAO.drawArrays(GL_TRIANGLES, 0, 36);

        // cam.move(glm::vec3(0, 0.005f, -0.01f));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true);
    }
}