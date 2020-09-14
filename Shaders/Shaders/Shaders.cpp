#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool VAO_1_active = true;
bool VAO_2_active = false;
bool VAO_e1_active = false;
bool VAO_e2_active = false;
bool VAO_e3_active = false;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
	Shader shader_1("shader_1.vs", "shader_1.fs");
	Shader shader_e1("shader_e1.vs", "shader_1.fs");
	Shader shader_e2("shader_e2.vs", "shader_1.fs");
	Shader shader_e3("shader_e3.vs", "shader_e3.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	float vertices_1[] = {
		// positions			// colors
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// bottom left 
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// top
	};

	// VAO/VBO construction (Uniforms) 
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// VAO/VBO construction (extra attributes)
	unsigned int VBO_1, VAO_1;
	glGenVertexArrays(1, &VAO_1);
	glGenBuffers(1, &VBO_1);
	glBindVertexArray(VAO_1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (VAO_1_active)
		{
			shader_0.use();

			float timeValue = glfwGetTime();
			float greenValue = sin(timeValue) / 2.0f + 0.5f;
			shader_0.setFloat("u_FragColor", greenValue);
			
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (VAO_2_active)
		{
			shader_1.use();

			glBindVertexArray(VAO_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (VAO_e1_active)
		{
			shader_e1.use();
			
			glBindVertexArray(VAO_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (VAO_e2_active)
		{
			shader_e2.use();

			shader_e2.setFloat("u_horizontalOffset", 0.25f);

			glBindVertexArray(VAO_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (VAO_e3_active)
		{
			shader_e3.use();

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
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
		VAO_1_active = true;
		VAO_2_active = false;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		VAO_1_active = false;
		VAO_2_active = true;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		VAO_1_active = false;
		VAO_2_active = false;
		VAO_e1_active = true;
		VAO_e2_active = false;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		VAO_1_active = false;
		VAO_2_active = false;
		VAO_e1_active = false;
		VAO_e2_active = true;
		VAO_e3_active = false;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		VAO_1_active = false;
		VAO_2_active = false;
		VAO_e1_active = false;
		VAO_e2_active = false;
		VAO_e3_active = true;
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

