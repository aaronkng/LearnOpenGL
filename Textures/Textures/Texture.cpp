#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

bool lesson_0_active = true;
bool lesson_1_active = false;
bool e0_active = false;
bool e1_active = false;
bool e2_active = false;
bool e3_active = false;

float mix = 0.2f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader_0("shader_0.vs", "shader_0.fs");
	Shader shader_1("shader_0.vs", "shader_1.fs");
	Shader shader_e1("shader_0.vs", "shader_e1.fs");
	Shader shader_e2("shader_0.vs", "shader_e2.fs");
	Shader shader_e3("shader_0.vs", "shader_0.fs");
	Shader shader_e4("shader_0.vs", "shader_e4.fs");

	float vertices[] = {
		// positions			// colors			// texture coordinates
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// bottom right 
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// bottom left 
		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f	// top left 
	};

	float vertices_e2[] = {
		// positions			// colors			// texture coordinates
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	2.0f, 2.0f, // top right
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	2.0f, 0.0f,	// bottom right 
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// bottom left 
		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 2.0f	// top left 
	};

	float vertices_e3[] = {
		// positions			// colors			// texture coordinates
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.55f, 0.55f, // top right
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.55f, 0.45f,	// bottom right 
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.45f, 0.45f,	// bottom left 
		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.45f, 0.55f	// top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle 
		1, 2, 3	 // second triangle 
	};

	// Lesson 0, Lesson 1, Exercise 0
	unsigned int VBO, VAO, EBO, VBO_e2, VAO_e2, VBO_e3, VAO_e3;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO_e2);
	glGenBuffers(1, &VBO_e2);

	glGenVertexArrays(1, &VAO_e3);
	glGenBuffers(1, &VBO_e3);

	// Lesson 0, Lesson 1, Exercise 0
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Exercise 2
	glBindVertexArray(VAO_e2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_e2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_e2), vertices_e2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Exercise 3
	glBindVertexArray(VAO_e3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_e3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_e3), vertices_e3, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Load and create a texture 
	unsigned int texture_0, texture_1, texture_e2, texture_e3;
	
	// texture_0
	glGenTextures(1, &texture_0);
	glBindTexture(GL_TEXTURE_2D, texture_0); // all upcoming GL_TEXTURE_2D operations now have an effect on this texture object
	// set texture wrapping parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture, and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture_1
	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	// set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture, and generate mipmaps
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture_e2
	glGenTextures(1, &texture_e2);
	glBindTexture(GL_TEXTURE_2D, texture_e2);
	// set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture, and generate mipmaps
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture_e3
	glGenTextures(1, &texture_e3);
	glBindTexture(GL_TEXTURE_2D, texture_e3);
	// set texture wrapping parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture, and generate mipmaps
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// tell opengl for sampler to which texture unit it belongs to (only has to be done once)
	shader_1.use(); // activate shader before setting uniforms 
	shader_1.setInt("u_texture_0", 0);
	shader_1.setInt("u_texture_1", 1);

	shader_e1.use();
	shader_e1.setInt("u_texture_0", 0);
	shader_e1.setInt("u_texture_1", 1);

	shader_e2.use();
	shader_e1.setInt("u_texture_0", 2);
	shader_e2.setInt("u_texture_1", 1);

	shader_e3.use();
	shader_e3.setInt("texture1", 3);

	shader_e4.use();
	shader_e4.setInt("u_texture_0", 0);
	shader_e4.setInt("u_texture_1", 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (lesson_0_active)
		{
			glBindTexture(GL_TEXTURE_2D, texture_0);
			shader_0.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		if (lesson_1_active)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_1);

			shader_1.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		if (e0_active)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_1);

			shader_e1.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		if (e1_active)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture_e2);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_1);

			shader_e2.use();
			glBindVertexArray(VAO_e2);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		if (e2_active)
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture_e3);
			shader_e3.use();
			glBindVertexArray(VAO_e3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		if (e3_active)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture_1);

			shader_e4.use();
			shader_e4.setFloat("mixFloat", mix);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		

		// swap buffers and poll IO events 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		lesson_0_active = true;
		lesson_1_active = false;
		e0_active = false;
		e1_active = false;
		e2_active = false;
		e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		lesson_0_active = false;
		lesson_1_active = true;
		e0_active = false;
		e1_active = false;
		e2_active = false;
		e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lesson_0_active = false;
		lesson_1_active = false;
		e0_active = true;
		e1_active = false;
		e2_active = false;
		e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lesson_0_active = false;
		lesson_1_active = false;
		e0_active = false;
		e1_active = true;
		e2_active = false;
		e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		lesson_0_active = false;
		lesson_1_active = false;
		e0_active = false;
		e1_active = false;
		e2_active = true;
		e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		lesson_0_active = false;
		lesson_1_active = false;
		e0_active = false;
		e1_active = false;
		e2_active = false;
		e3_active = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && mix <= 1.0f)
	{
		mix += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && mix >= 0.0f)
	{
		mix -= 0.01f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}