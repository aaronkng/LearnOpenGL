#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);

// screen settings 
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera settings 
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing 
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2, 1.0f, 2.0f);

bool lesson_0 = true;
bool lesson_1 = false;
bool lesson_2 = false;
bool exercise_0 = false;
bool exercise_1 = false;

int main()
{
	// glfw: initialize and configure 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad:: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	Shader lightingShader_L0("lesson_0.vs", "lesson_0.fs");
	Shader lightingShader_L1("lesson_0.vs", "lesson_1.fs");
	Shader lightCubeShader("light_cube.vs", "light_cube.fs");
	Shader lightCubeShader_E0("light_cube.vs", "light_cube_e0.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

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
	
	// configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)
		(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// configure the light's VAO
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// render loop 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// per-frame time logic 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
			(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		if (lesson_0 || exercise_1)
		{
			lightingShader_L0.use();
			lightingShader_L0.setVec3("viewPos", camera.Position);

			// light properties 
			lightingShader_L0.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			lightingShader_L0.setVec3("lightPos", lightPos);

			// material properties 
			if (lesson_0) 
			{
				lightingShader_L0.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
				lightingShader_L0.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
				lightingShader_L0.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
				lightingShader_L0.setFloat("material.shininess", 32.0f);
			}
			
			if (exercise_1)
			{
				lightingShader_L0.setVec3("material.ambient", 0.25f, 0.25f, 0.25f);
				lightingShader_L0.setVec3("material.diffuse", 0.4f, 0.4f, 0.4f);
				lightingShader_L0.setVec3("material.specular", 0.774597f, 0.774597f, 0.774597f);
				lightingShader_L0.setFloat("material.shininess", 64.0f);
			}

			// render the cube
			lightingShader_L0.setMat4("projection", projection);
			lightingShader_L0.setMat4("view", view);
			lightingShader_L0.setMat4("model", model);
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		if (lesson_1 || lesson_2 || exercise_0)
		{
			lightingShader_L1.use();
			lightingShader_L1.setVec3("viewPos", camera.Position);

			// light properties 
			glm::vec3 lightColor;
			glm::vec3 diffuseColor;
			glm::vec3 ambientColor;
			if (lesson_1)
			{
				lightColor = glm::vec3(1.0f);
				diffuseColor = lightColor * glm::vec3(0.5f);
				ambientColor = lightColor * glm::vec3(0.2f);
			}

			if (lesson_2 || exercise_0)
			{
				lightColor.x = sin(glfwGetTime() * 2.0f);
				lightColor.y = sin(glfwGetTime() * 0.7f);
				lightColor.z = sin(glfwGetTime() * 1.3f);

				diffuseColor = lightColor * glm::vec3(0.5f);
				ambientColor = diffuseColor * glm::vec3(0.2f);
				
				lightCubeShader_E0.use();
				lightCubeShader_E0.setVec3("ambient", ambientColor);
				lightCubeShader_E0.setVec3("diffuse", diffuseColor);
				lightCubeShader_E0.setVec3("specular", 1.0f, 1.0f, 1.0f);
			}

			lightingShader_L1.use();
			lightingShader_L1.setVec3("light.position", lightPos);
			lightingShader_L1.setVec3("light.ambient", ambientColor);
			lightingShader_L1.setVec3("light.diffuse", diffuseColor);
			lightingShader_L1.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

			// material properties 
			lightingShader_L1.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
			lightingShader_L1.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
			lightingShader_L1.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
			lightingShader_L1.setFloat("material.shininess", 32.0f);

			// render the cube
			lightingShader_L1.setMat4("projection", projection);
			lightingShader_L1.setMat4("view", view);
			lightingShader_L1.setMat4("model", model);
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// draw the lamp object
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		if (lesson_0 || lesson_1 || lesson_2 || exercise_1)
		{
			lightCubeShader.use();
			lightCubeShader.setMat4("projection", projection);
			lightCubeShader.setMat4("view", view);
			lightCubeShader.setMat4("model", model);
		}
		if (exercise_0)
		{
			lightCubeShader_E0.use();
			lightCubeShader_E0.setMat4("projection", projection);
			lightCubeShader_E0.setMat4("view", view);
			lightCubeShader_E0.setMat4("model", model);
		}
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		lesson_0 = true;
		lesson_1 = false;
		lesson_2 = false;
		exercise_0 = false;
		exercise_1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = true;
		lesson_2 = false;
		exercise_0 = false;
		exercise_1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = false;
		lesson_2 = true;
		exercise_0 = false;
		exercise_1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = false;
		lesson_2 = false;
		exercise_0 = true;
		exercise_1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		lesson_0 = false;
		lesson_1 = false;
		lesson_2 = false;
		exercise_0 = false;
		exercise_1 = true;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}