#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

bool lesson_0 = true;
bool lesson_1 = false;
bool lesson_2 = false;
bool exercsie_0 = false;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// GLFW: initailzie and configure 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: load all OpenGL function poitners
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader_L0("shader_L0.vs", "shader_L0.fs");

	glEnable(GL_DEPTH_TEST);

	// Set up vertex data and buffers, and configure vertex attributes
	float vertices_L0[] = {
		// positions			// texture coordinates
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		// top right
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// bottom left 
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f		// top left
	};
	unsigned int indices_L0[] = {
	0, 1, 3,	// first triangle
	1, 2, 3		// second triangle
	};
	float vertices_L1[] = {
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
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	unsigned int VBO_L0, VBO_L1, VAO_L0, VAO_L1, EBO_L0;
	glGenVertexArrays(1, &VAO_L0);
	glGenBuffers(1, &VBO_L0);
	glGenBuffers(1, &EBO_L0);
	glGenVertexArrays(1, &VAO_L1);
	glGenBuffers(1, &VBO_L1);
	// Lesson 0 buffer data
	glBindVertexArray(VAO_L0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_L0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_L0), vertices_L0, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_L0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_L0), indices_L0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Lesson 1 buffer data
	glBindVertexArray(VAO_L1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_L1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_L1), vertices_L1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture_0, texture_1;
	// texture 0
	glGenTextures(1, &texture_0);
	glBindTexture(GL_TEXTURE_2D, texture_0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	// texture 1
	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader_L0.use();
	shader_L0.setInt("texture_0", 0);
	shader_L0.setInt("texture_1", 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_1);

		shader_L0.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		if (lesson_0)
		{
			// create transforms
			model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader_L0.setMat4("model", model);
			shader_L0.setMat4("view", view);
			shader_L0.setMat4("projection", projection);

			// render container
			glBindVertexArray(VAO_L0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		
		if (lesson_1)
		{
			// create transforms
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader_L0.setMat4("model", model);
			shader_L0.setMat4("view", view);
			shader_L0.setMat4("projection", projection);

			// render container
			glBindVertexArray(VAO_L1);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		if (lesson_2)
		{
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader_L0.setMat4("view", view);
			shader_L0.setMat4("projection", projection);

			glBindVertexArray(VAO_L1);
			for (int i = 0; i < 10; i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader_L0.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		if (exercsie_0)
		{
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader_L0.setMat4("view", view);
			shader_L0.setMat4("projection", projection);

			// Draw first rotating cube
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[0]);
			float angle = 20.0f;
			model = glm::rotate(model, (float)glfwGetTime() + glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader_L0.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(VAO_L1);
			for (int i = 1; i < 10; i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				if(i % 3 == 0)
					model = glm::rotate(model, (float)glfwGetTime() + glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				else
					model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader_L0.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO_L0);
	glDeleteBuffers(1, &VBO_L0);
	glDeleteBuffers(1, &EBO_L0);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		lesson_0 = true;
		lesson_1 = false;
		lesson_2 = false;
		exercsie_0 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = true;
		lesson_2 = false;
		exercsie_0 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = false;
		lesson_2 = true;
		exercsie_0 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = false;
		lesson_2 = false;
		exercsie_0 = true;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}