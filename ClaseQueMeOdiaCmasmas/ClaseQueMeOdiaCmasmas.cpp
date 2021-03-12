// ClaseQueMeOdiaCmasmas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//medidas de la pantalla

const unsigned int largo = 800;
const unsigned int ancho = 800;

const char* vertexShaderSource = "#version 330 core \n"
"layout(location =0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z,1.0);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"FragColor = vec4(0.5f,0.2f,0.8f,1.0f);\n"
"}\n\0";

int main()
{
	//inicializamos glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creacion de nuestra ventanita hermosa bella de chula
	GLFWwindow* window = glfwCreateWindow(largo, ancho, "tortita", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "fallaste, mejor llora XD" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "oye wey no se esta ejecutando el alegre" << std::endl;
		return -1;
	}
	//inicializaciones
	//inicializacion del vertex
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//Comprobacion del vertex
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error error error \n" << infoLog << std::endl;
	}

	//inicializacion del fragment
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Comprobacion del fragment

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error error error \n" << infoLog << std::endl;
	}

	//inicializamos el programa
	//linkeamos todo

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//comprobar los linkeos
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Erroasdfwsafs error error \n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	std::cout << "Inicializando" << std::endl;
	//configuramos el objeto
	float vertices[]{
		/*castillo mamalon*/
		-1.0f, -1.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,
		 1.0f,	-0.5f, 0.0f,

		 -1.0f, -0.5f, 0.0f,
		 -1.0f, -1.0f, 0.0f,
		 1.0f,	-0.5f, 0.0f,

		 -1.0f, -0.5f, 0.0f,
		 -0.8f, -0.5f, 0.0f,
		 -1.0f,	-0.3f, 0.0f,

		 -1.0f, -0.3f, 0.0f,
		 -0.8f, -0.5f, 0.0f,
		 -0.8f,	-0.3f, 0.0f,


		 -1.0f, -0.3f, 0.0f,
		 -0.8f, -0.3f, 0.0f,
		 -0.9f,	-0.1f, 0.0f,
		 
		 1.0f, -0.5f, 0.0f,
		 0.8f, -0.5f, 0.0f,
		 1.0f,	-0.3f, 0.0f,

		 1.0f, -0.3f, 0.0f,
		 0.8f, -0.5f, 0.0f,
		 0.8f,	-0.3f, 0.0f,

		 1.0f, -0.3f, 0.0f,
		 0.8f, -0.3f, 0.0f,
		 0.9f,	-0.1f, 0.0f,
		 
		 -0.2f, -0.5f, 0.0f,
		 0.2f, -0.5f, 0.0f,
		  -0.2f,  0.2f, 0.0f,

		  -0.2f, 0.2f, 0.0f,
		   0.2f, 0.2f, 0.0f,
		   0.2f,  -0.5f, 0.0f,

		  -0.2f, 0.2f, 0.0f,
		   0.2f, 0.2f, 0.0f,
		   0.0f,  0.4f, 0.0f,
		 
		  -0.03f, 0.2f, 0.0f,
		   0.03f, 0.2f, 0.0f,
		   -0.03f,  0.5f, 0.0f,

		   -0.03f, 0.5f, 0.0f,
		   0.03f, 0.5f, 0.0f,
		   0.03f,  0.2f, 0.0f,

			-0.03f, 0.5f, 0.0f,
		   0.03f, 0.5f, 0.0f,
		   0.03f,  0.2f, 0.0f,

		   0.03f, 0.5f, 0.0f,
		   0.1f, 0.5f, 0.0f,
		   0.03f,  0.45f, 0.0f

		 /*
		//figura fea que no se como se llama
		-1.0f, 0.5f, 0.0f,
		-0.0f, 0.5f, 0.0f,
		-0.5f, 1.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-0.0f, 0.0f, 0.0f,
		-1.0f, 0.5f, 0.0f,

		-1.0f, 0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		 0.0f, 0.0f, 0.0f,

		-1.0f, -0.0f, 0.0f,
		 0.0f, -0.0f, 0.0f,
		 -0.5f, -0.5f, 0.0f,

		 //nave espacial
		0.2f, 0.2f, 0.0f,
		0.4f, 0.2f, 0.0f,
		0.3f, 0.8f, 0.0f,
		
		0.1f, 0.3f, 0.0f,
		0.5f, 0.3f, 0.0f,
		0.3f, 0.5f, 0.0f,

		0.1f, 0.3f, 0.0f,
		0.5f, 0.3f, 0.0f,
		0.3f, 0.2f, 0.0f,

		0.2f, 0.2f, 0.0f,
		0.4f, 0.2f, 0.0f,
		0.3f, 0.15f, 0.0f,

		//triangulos randoms
		0.1f, -0.3f, 0.0f,
		0.4f, -0.3f, 0.0f,
		0.3f, -0.4f, 0.0f,

		0.5f, -0.6f, 0.0f,
		0.7f, -0.6f, 0.0f,
		0.7f, -0.8f, 0.0f,

		-0.0f, -0.5f, 0.0f,
		-0.4f, -0.6f, 0.0f,
		-0.3f, -0.7f, 0.0f,
		*/
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//unificamos
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);

	//Habilitar nuestros atributos
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//generacion del ciclo de dibujado
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//color
		glClearColor(0.5f, 0.2f, 0.3f, 1.0f);

		//dibujar
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 45);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
