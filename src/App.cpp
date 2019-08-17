#include "common/renderer.h"
#include "shader/shader.h"

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

	Shader shader("./shader/first.vertexShader", "./shader/first.fragmentShader");
	shader.use();

	float vertices[] = {
		-0.5f,  -0.5f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		 0.0f,   0.5f, 0.0f
	};

	GLCall(glGenVertexArrays(1, &context.vao));
	GLCall(glBindVertexArray(context.vao));

	GLCall(glGenBuffers(1, &context.vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, context.vbo))

	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void *) vertices, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
	GLCall(glEnableVertexAttribArray(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(context.window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		shader.use();

		GLCall(glBindVertexArray(context.vao));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		/* Swap front and back buffers */
		glfwSwapBuffers(context.window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}