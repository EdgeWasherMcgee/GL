#include "common/renderer.h"
#include "shader/shader.h"
#include "objects/vertexBuffer.h"
#include "objects/indexBuffer.h"
#include "objects/vao.h"

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;   // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, width*0.625);
}

struct vertexWithColor {

    float positions[3];
    float rgb[3];
};

int main(void) {
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    if(GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glViewport(0, 0, 1280, 1280*0.625);


    /* Make the window's context current */

    Shader shader("shader/first.vertexShader", "shader/first.fragmentShader");
    shader.use();

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_FRAMEBUFFER_SRGB));
    // GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

    float vertices[] = {

        -1.0f, -1.0f,  1.0f, 1.000f, 1.000f, 1.000f, //Front down left 0
         1.0f, -1.0f,  1.0f, 1.000f, 0.000f, 1.000f, //Front down right 1
        -1.0f,  1.0f,  1.0f, 0.000f, 1.000f, 1.000f, //Front up left 2
         1.0f,  1.0f,  1.0f, 0.000f, 0.000f, 1.000f, //Front up right 3
        -1.0f, -1.0f, -1.0f, 1.000f, 1.000f, 0.000f, //Back down left 4
         1.0f, -1.0f, -1.0f, 1.000f, 0.000f, 0.000f, //Back down right 5
        -1.0f,  1.0f, -1.0f, 0.000f, 1.000f, 0.000f, //Back up left 6
         1.0f,  1.0f, -1.0f, 0.000f, 0.000f, 0.000f, //Back up right 7
    };

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

    VertexArray VAO;

    VAO.VBO.bufferData(sizeof(vertices), (void *) vertices);
    VAO.IBO.bufferData(sizeof(indices), indices);

    GLuint indexCount = sizeof(indices)/sizeof(unsigned short);

    VAO.addAttribute(GL_FLOAT, 3);
    VAO.addAttribute(GL_FLOAT, 3);

    glm::mat4 modelMatrix(1);
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 viewMatrix(1);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1280.0f/960.0f, 0.1f, 100.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));

        viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shader.setUniform("modelMatrix", modelMatrix);
        shader.setUniform("viewMatrix", viewMatrix);
        shader.setUniform("perspectiveMatrix", perspectiveMatrix);

        shader.use();

        VAO.drawElements(GL_TRIANGLES, indexCount);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 0.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}