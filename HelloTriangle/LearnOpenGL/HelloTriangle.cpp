#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool VAO_0_active = true;
bool VAO_1_active = false;
bool VAO_e1_active = false;
bool VAO_e2_active = false;
bool VAO_e3_active = false; 

const char* vertexShaderSource_0 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource_0 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource_1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0, 1.0f);\n"
"}\n\0";

int main()
{
	// Initialize GLFW and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Build and compile vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource_0, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Build and compile fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource_0, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Second fragment shader (Exercise 3)
	int fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fragmentShaderSource_1, NULL);
	glCompileShader(fragmentShader_1);
	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders 
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	int shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);
	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader_1);

	// Set up vertex data and buffers and configure vertex attributes for single triangle
	float vertices_0[] = {
		-0.5f, -0.5f, 0.0f,	// left
		0.5f, -0.5f, 0.0f,	// right
		0.0f, 0.5f, 0.0f	// top
	};
	unsigned int VBO_0, VAO_0;
	glGenVertexArrays(1, &VAO_0);
	glGenBuffers(1, &VBO_0);
	// Bind VAO first, then bind and set VBO, then configure vertex attributes
	glBindVertexArray(VAO_0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_0), vertices_0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set up vertex data and buffers for rectangle
	float vertices_1[] = {
	0.5f, 0.5f, 0.0f,	// top right
	0.5f, -0.5f, 0.0f,	// bottom right 
	-0.5f, -0.5f, 0.0f,	// bottom left 
	-0.5f, 0.5f, 0.0f	// top left
	};
	unsigned int indices[] = {
		0, 1, 3,	// first triangle 
		1, 2, 3		// second triangle
	};
	unsigned int VBO_1, VAO_1, EBO;
	glGenVertexArrays(1, &VAO_1);
	glGenBuffers(1, &VBO_1);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO_1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Exercise 1
	float vertices_e1[] = {
		// Left triangle
		-0.5f, 0.5f, 0.0f, 
		-1.0f, -0.5f, 0.0f, 
		0.0f, -0.5f, 0.0f,
		// Right traingle 
		0.5f, 0.5f, 0.0f, 
		1.0f, -0.5f, 0.0f, 
		0.0f, -0.5f, 0.0f
	};
	unsigned int VBO_e1, VAO_e1;
	glGenVertexArrays(1, &VAO_e1);
	glGenBuffers(1, &VBO_e1);
	glBindVertexArray(VAO_e1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_e1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_e1), vertices_e1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Exercise 2
	float vertices_e2_0[] = {	// Left triangle
		-0.5f, 0.5f, 0.0f, 
		-1.0f, -0.5f, 0.0f, 
		0.0f, -0.5f, 0.0f
	};
	float vertices_e2_1[] = {	// Right triangle
		0.5f, 0.5f, 0.0f, 
		1.0f, -0.5f, 0.0f, 
		0.0f, -0.5f, 0.0f
	};
	unsigned int VBO_e2[2], VAO_e2[2];
	glGenVertexArrays(2, VAO_e2);
	glGenBuffers(2, VBO_e2);
	
	glBindVertexArray(VAO_e2[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_e2[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_e2_0), vertices_e2_0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(VAO_e2[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_e2[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_e2_1), vertices_e2_1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw triangle 
		if (VAO_0_active)
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO_0); 
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		// Draw rectangle 
		if (VAO_1_active)
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO_1);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		// Draw exercise one 
		if (VAO_e1_active)
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO_e1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// Draw exercise two 
		if (VAO_e2_active)
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO_e2[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(VAO_e2[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (VAO_e3_active)
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO_e2[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glUseProgram(shaderProgram_1);
			glBindVertexArray(VAO_e2[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		// GLFW: swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GLFW: terminate, clear all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}

// GFLW: when window size changes, this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Process all input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		VAO_0_active = true;
		VAO_1_active = false;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		VAO_0_active = false;
		VAO_1_active = true;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		VAO_0_active = false;
		VAO_1_active = false;
		VAO_e1_active = true;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		VAO_0_active = false;
		VAO_1_active = false;
		VAO_e1_active = false;
		VAO_e2_active = true;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		VAO_0_active = false;
		VAO_1_active = false;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = true;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}