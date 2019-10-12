#include "common/renderer.h"
#include "shader/shader.h"
#include "objects/vertexBuffer.h"
#include "objects/indexBuffer.h"
#include "objects/vao.h"
#include "camera.h"

glm::vec3 acceleration = glm::vec3(0);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

Camera cam;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, width*0.625f);
}

struct VertexPositionWithNormals {

    float pos[3];
    float normals[3];

};

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
    GLFWwindow* window = glfwCreateWindow(1500, 900, "Not rotating cube", NULL, NULL);

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
    // glViewport(0, 0, 1000, 600);

    /* Make the window's context current */

    Shader shader("shader/first.vertexShader", "shader/first.fragmentShader");
    Shader lightShader("shader/light.vertexShader", "shader/light.fragmentShader");
    shader.use();

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_FRAMEBUFFER_SRGB));

    float vertices[] = {

        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // VertexPositionWithNormals vertices[] = {

    //     {{-1.0f, -1.0f, -1.0f}, {  }}, //Front left down 0
    //     {{-1.0f, -1.0f,  1.0f}, {  }}, //Front right down 1
    //     {{-1.0f,  1.0f, -1.0f}, {  }}, //Front left up 2
    //     {{-1.0f,  1.0f,  1.0f}, {  }}, //Front right up 3
    //     {{ 1.0f, -1.0f, -1.0f}, {  }}, //Back left down 4
    //     {{ 1.0f, -1.0f,  1.0f}, {  }}, //Back right down 5
    //     {{ 1.0f,  1.0f, -1.0f}, {  }}, //Back left up 6
    //     {{ 1.0f,  1.0f,  1.0f}, {  }}, //Back right up 7
    // };

    // unsigned short indices[] = {

    //     0, 1, 2,
    //     3, 2, 1,
        
    //     1, 5, 3,
    //     5, 3, 7,
        
    //     7, 6, 5,
    //     4, 5, 6,
        
    //     0, 4, 2,
    //     4, 2, 6,
        
    //     2, 3, 6,
    //     7, 6, 3,
        
    //     0, 1, 4,
    //     1, 4, 5,

    // };

    VertexArray VAO;

    VAO.VBO.bufferData(sizeof(vertices), (void *) vertices);
    // VAO.IBO.bufferData(sizeof(indices), indices);

    // GLuint indexCount = sizeof(indices)/sizeof(unsigned short);
    GLuint vertexCount = sizeof(vertices)/(sizeof(float) * 2);

    VAO.addAttribute(GL_FLOAT, 3);
    VAO.addAttribute(GL_FLOAT, 3);

    glm::mat4 u_modelMatrix1(1);
    glm::mat4 u_modelMatrix2(1);

    // u_modelMatrix[3][0] = 10;
    // u_modelMatrix[0][3] = -10.0f;

    cam.setPos(glm::vec3(0.0f, 0.0f, -10.0f));
    cam.lookAt(glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec3 objectColor = glm::vec3(0.0f, 0.5f, 0.5f);

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    u_modelMatrix1[0][0] = 0.5;
    u_modelMatrix1[1][1] = 0.5;
    u_modelMatrix1[2][2] = 0.5;
    u_modelMatrix1[3][0] = 3;
    u_modelMatrix1[3][1] = 3;
    u_modelMatrix1[3][2] = 3;

    u_modelMatrix2[0][0] = 2.0;
    u_modelMatrix2[1][1] = 2.0;
    u_modelMatrix2[2][2] = 2.0;
    u_modelMatrix2[3][0] = 0;
    u_modelMatrix2[3][1] = 0;
    u_modelMatrix2[3][2] = 0;

    glm::mat4 matrix;
    glm::mat4 lastViewMatrix = glm::mat4(1);
    printf("%d\n", vertexCount);

    // modelMatrix = glm::rotate(modelMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // u_modelMatrix1 = glm::rotate(u_modelMatrix1, 0.05f, glm::vec3(0.3f, 0.7f, 0.5f));
        // u_modelMatrix2 = glm::rotate(u_modelMatrix2, -0.05f, glm::vec3(0.3f, 0.7f, 0.5f));

        // printf("%fms, %f fps\n", deltaTime, (1/deltaTime));

        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));

        cam.lookAt(glm::vec3(3.0f, 3.0f, 3.0f));

        matrix = cam.getPerspectiveMatrix() * cam.getViewMatrix() * u_modelMatrix2;

        shader.use();
        shader.setUniform("matrix", matrix);
        shader.setUniform("objColor", objectColor);
        shader.setUniform("lightColor", lightColor);
        shader.setUniform("viewPos", cam.getPos());
        shader.setUniform("lightPos", glm::vec3(3, 3, 3));
        shader.setUniform("model", u_modelMatrix2);

        VAO.drawArrays(GL_TRIANGLES, 0, vertexCount);

        matrix = cam.getPerspectiveMatrix() * cam.getViewMatrix() * u_modelMatrix1;

        lightShader.use();
        shader.setUniform("matrix", matrix);

        VAO.drawArrays(GL_TRIANGLES, 0, vertexCount);

        lastViewMatrix = cam.getViewMatrix();

        cam.move(cam.getFront() * acceleration.z + cam.getUp() * acceleration.y + cam.getSide() * acceleration.x);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const float speed = 0.1f;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true);

    } else if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            acceleration.z = speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.z = 0;
        }

    } else if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            acceleration.z = -speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.z = 0;
        }

    } else if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            acceleration.x = -speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.x = 0;
        }

    } else if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            acceleration.x = speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.x = 0;
        }

    } else if (key == GLFW_KEY_Q) {
        if (action == GLFW_PRESS) {
            acceleration.y = speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.y = 0;
        }

    } else if (key == GLFW_KEY_E) {
        if (action == GLFW_PRESS) {
            acceleration.y = -speed;
        } else if (action == GLFW_RELEASE) {
            acceleration.y = 0;
        }

    }
}