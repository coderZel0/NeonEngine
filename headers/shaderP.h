#ifndef SHADER_H
#define SHADER_H

#include<iostream>
#include<glad/glad.h>
#include<glm/glm/glm.hpp>

#include<string>
#include<fstream>
#include<sstream>


class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vertexCode, fragmentCode;
		
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(std::ifstream::failure& e){
			std::cout << "SHADER_FILE::NOT_READ" << std:: endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	};
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string &name,bool value)const
	{
		glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
	}
	void setInt(const std::string &name, int value)const
	{
		glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
	}
	void setFloat(const std::string& name, float value)const
	{
		glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
	}
	void setMat4(const std::string &name,glm::mat4 mat){
		glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&mat[0][0]);
	}
private:
	void checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[512];
		if (type != "PROGRAM") {
			glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cout <<type<< "SHADER::COMPILE::ERROR" << infoLog << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << "PROGRAM::LINK::ERROR" << infoLog << std::endl;
			}
		}
	}

};

#endif