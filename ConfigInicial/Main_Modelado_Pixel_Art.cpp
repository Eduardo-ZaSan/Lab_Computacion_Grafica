//Nombre: Eduardo Zavala Sanchez
//NumCuenta:318105538
//Practica 4 Modelado
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1000, HEIGHT = 800;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Modelado Eduardo Zavala Sanchez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 0.0745f, 0.5059f,0.7137f,
		0.5f,  0.5f, -0.5f,  0.0745f, 0.5059f,0.7137f,
		0.5f,  0.5f,  0.5f,  0.0745f, 0.5059f,0.7137f,
		0.5f,  0.5f,  0.5f,  0.0745f, 0.5059f,0.7137f,
		-0.5f,  0.5f,  0.5f, 0.0745f, 0.5059f,0.7137f,
		-0.5f,  0.5f, -0.5f, 0.0745f, 0.5059f,0.7137f,
		//NEGRO
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,0.0f,
		//BLANCO
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,1.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,

		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 1.0f, 1.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,1.0f,
		//Piel azul Lapras
			-0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,//Front
			0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			-0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			-0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,

			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,//Back
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,

			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, 0.5f, -0.5f, 0.1098f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.1098f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.1098f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.1098f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.1098f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.1098f, 1.0f, 1.0f,
			//Piel Amarilla Lapras
			-0.5f, -0.5f, 0.5f, 0.9137, 0.8588, 0.5216,//Front
			0.5f, -0.5f, 0.5f, 0.9137, 0.8588, 0.5216,
			0.5f, 0.5f, 0.5f, 0.9137, 0.8588, 0.5216,
			0.5f, 0.5f, 0.5f, 0.9137, 0.8588, 0.5216,
			-0.5f, 0.5f, 0.5f, 0.9137, 0.8588, 0.5216,
			-0.5f, -0.5f, 0.5f, 0.9137, 0.8588, 0.5216,

			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,//Back
			0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,

			0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,

			-0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,

			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, -0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,

			-0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, 0.5f, 0.5f, 0.7255f, 0.6784f, 0.3843f,
			-0.5f, 0.5f, -0.5f, 0.7255f, 0.6784f, 0.3843f,
			//Piel Azul (sombra)
			-0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,//Front
			0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			-0.5f, 0.5f, 0.5f, 0.0784, 0.7882, 0.851,
			-0.5f, -0.5f, 0.5f, 0.0784, 0.7882, 0.851,

			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,//Back
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,

			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, -0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,

			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, 0.5f, 0.0588f, 0.6706f, 0.7333f,
			-0.5f, 0.5f, -0.5f, 0.0588f, 0.6706f, 0.7333f,

			//Caparazon 1
				-0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,//Front
				0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,

				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,//Back
				0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,

				0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,

				-0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,//
				-0.5f, 0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, 0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,

				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, 0.5f, 0.1608f, 0.302f, 0.4196f,
				-0.5f, -0.5f, -0.5f, 0.1608f, 0.302f, 0.4196f,

				-0.5f, 0.5f, -0.5f, 0.2784f, 0.4706f, 0.6118f,
				0.5f, 0.5f, -0.5f, 0.2784f, 0.4706f, 0.6118f,
				0.5f, 0.5f, 0.5f, 0.2784f, 0.4706f, 0.6118f,
				0.5f, 0.5f, 0.5f, 0.2784f, 0.4706f, 0.6118f,
				-0.5f, 0.5f, 0.5f, 0.2784f, 0.4706f, 0.6118f,
				-0.5f, 0.5f, -0.5f, 0.2784f, 0.4706f, 0.6118f,
	};



	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		//Pata 2 mesa
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.1f)); //tamano de la pata
		//model = glm::translate(model, glm::vec3(-2.9f, -0.6f, 1.9f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 1.2f)); 
		model = glm::translate(model, glm::vec3(0.0f, 0.17f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 1.0f)); 
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, -0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, -0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.6f));
		model = glm::translate(model, glm::vec3(0.0f, 4.5f, -0.539f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.225f));
		model = glm::translate(model, glm::vec3(0.0f, 4.5f, 0.38f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.709f));
		model = glm::translate(model, glm::vec3(0.0f, -1.499f, 0.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 216);
		/*model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, -0.4f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		//OREJAS
			//IZQUIERDA
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(2.0f, 4.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(1.24f, 5.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(3.0f, 4.5f, -3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
			//DERECHA	
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(-2.0f, 4.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(-1.24f, 5.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-3.0f, 4.5f, -3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		//Costado Derecho

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.3f)); 
		model = glm::translate(model, glm::vec3(2.0f, 0.299f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.2f)); 
		model = glm::translate(model, glm::vec3(2.0f, 0.834f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); 
		model = glm::translate(model, glm::vec3(2.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.3f));
		model = glm::translate(model, glm::vec3(3.0f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		//Costado Izquierdo

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.3f)); 
		model = glm::translate(model, glm::vec3(-2.0f, 0.299f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.2f)); 
		model = glm::translate(model, glm::vec3(-2.0f, 0.834f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); 
		model = glm::translate(model, glm::vec3(-2.0f, 1.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.3f));
		model = glm::translate(model, glm::vec3(-3.0f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		//OJOS
		//Derecho
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f)); //tamano del ojo negro
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f)); //tamano del ojo negro
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		//Izquierdo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f)); //tamano del ojo negro
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f)); //tamano del ojo negro
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		//CUERPO
		
		model = glm::mat4(1.0f);  //Espalda 
		model = glm::scale(model, glm::vec3(0.6f, 2.2f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -1.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		
		model = glm::mat4(1.0f);  //Abdomen amarillo
		model = glm::scale(model, glm::vec3(0.6f, 1.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, -0.64f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		model = glm::mat4(1.0f); //Boca
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		model = glm::mat4(1.0f);//brazo derecho
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(2.0f, -1.5f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.0f, -1.5f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);

		model = glm::mat4(1.0f);  //Abdomen azul
		model = glm::scale(model, glm::vec3(0.6f, 1.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, -0.64f, -3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f);//brazo derecho
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(2.0f, -1.5f, -3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.0f, -1.5f, -3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);



		//Patas
		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(-1.75f, -6.5f, -1.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.6f));
		model = glm::translate(model, glm::vec3(-2.25f, -7.5f, -1.338f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.4f));
		model = glm::translate(model, glm::vec3(-3.0f, -3.0f, -2.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 104);

		model = glm::mat4(1.0f); //brazo derecho
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(1.75f, -6.5f, -1.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo derecho
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.6f));
		model = glm::translate(model, glm::vec3(2.25f, -7.5f, -1.338f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo derecho
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.4f));
		model = glm::translate(model, glm::vec3(3.0f, -3.0f, -2.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 104);

		//Patas traseras

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(-1.75f, -7.5f, -4.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::mat4(1.0f); //brazo izquierdo
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(1.75f, -7.5f, -4.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		//Panza Plana

		model = glm::mat4(1.0f); //brazo derecho
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 1.6f));
		model = glm::translate(model, glm::vec3(0.0f, -7.5f, -0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 104);

		//Caparazon
		model = glm::mat4(1.0f); //Centro
		model = glm::scale(model, glm::vec3(0.6f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, -2.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //Centro
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -3.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //Centro
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -8.89f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.6f));
		model = glm::translate(model, glm::vec3(-2.0f, -1.1f, -1.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.0f, -1.5f, -6.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla aun mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.0f, -2.165f, -7.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.0f, -3.5f, -8.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.6f));
		model = glm::translate(model, glm::vec3(2.0f, -1.1f, -1.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(2.0f, -1.5f, -6.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla aun mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3(2.0f, -2.165f, -7.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(2.0f, -3.5f, -8.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		/////////////////////////

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(3.0f, -2.5f, -6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(3.0f, -3.0f, -7.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(-3.0f, -2.5f, -6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);

		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(-3.0f, -3.0f, -7.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 252);
		//Piso
		model = glm::mat4(1.0f); //orilla la mas pequena
		model = glm::scale(model, glm::vec3(20.0f, 0.6f, 20.0f));
		model = glm::translate(model, glm::vec3(0.0f, -3.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.01f;
}


