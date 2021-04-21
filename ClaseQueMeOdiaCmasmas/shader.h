#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	//CONSTRUCTOR PARA GENERAR NUESTROS SHADERS
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		//obtener cidigo de vertex y fragment mediante un archivo
		std::string vertexCode;
		std::string fragmentCode;
		std::string geeometryCode;
		std::ifstream vShaderfile;
		std::ifstream fShaderfile;
		std::ifstream gShaderfile;
		//generar excepciones
		vShaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			//abrir los archivos
			vShaderfile.open(vertexPath);
			fShaderfile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//leer todos los arreglos del codigo y almacenarlo en los buffers
			vShaderStream << vShaderfile.rdbuf();
			fShaderStream << fShaderfile.rdbuf();
			vShaderfile.close();
			fShaderfile.close();
			//Convertir el codigo a string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			if (geometryPath != nullptr)
			{
				gShaderfile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderfile.rdbuf();
				gShaderfile.close();
				geeometryCode = vShaderStream.str();
			}

		}
		catch (std::ifstream::failure& e) {
			std::cout << "Error en la carga de archivos del shader" << std
				::endl;
		}
		const char* vshaderCode = vertexCode.c_str();
		const char* fshaderCode = fragmentCode.c_str();

		//Compilar los shaders
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vshaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fshaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//checar geometria
		unsigned int geo;
		if (geometryPath != nullptr)
		{
			const char* gShaderCode = geeometryCode.c_str();
			geo = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geo, 1, &gShaderCode, NULL);
			glCompileShader(geo);
			checkCompileErrors(geo, "GEOMETRY");
		}
		//linkeos
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geo);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geo);
		//activar shaders
	}
		void use()
		{
			glUseProgram(ID);
		}

		//declarar nuestras funciones de utilidad par
		//que entienda los atributos de nustros shaders
		void setBool(const std::string & nombre, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, nombre.c_str()), (int)value);
		}

		void setInt(const std::string & nombre, int value) const
		{
			glUniform1i(glGetUniformLocation(ID, nombre.c_str()), value);
		}

		void setFloat(const std::string & nombre, float value) const
		{
			glUniform1i(glGetUniformLocation(ID, nombre.c_str()), value);
		}

		void setVec2(const std::string & name, const glm::vec2 & value) const
		{
			glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void setVec2(const std::string & name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
		}

		void setVec3(const std::string & name, const glm::vec3 & value) const
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void setVec3(const std::string & name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
		}

		void setVec4(const std::string & name, const glm::vec4 & value) const
		{
			glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		void setVec4(const std::string & name, float x, float y, float z, float w)
		{
			glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
		}
		void setMat2(const std::string & name, const glm::mat2 & mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		void setMat3(const std::string & name, const glm::mat3 & mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		void setMat4(const std::string & name, const glm::mat4 & mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
	

		void checkCompileErrors(GLuint shader, std::string type)
		{
			GLint success;
			GLchar infoLog[1024];
			if (type != "PROGRAM")
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "error no se pudo compilar los shaders" << type << "\n" << infoLog << std::endl;
				}
			}
			else
			{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "error, no se pudo linkear el programa" << type << "\n" << infoLog << std::endl;
				}
			}
		}

	};

#endif