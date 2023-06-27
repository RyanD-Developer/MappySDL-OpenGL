#include "ShaderUtil.h"

#include <gtc/type_ptr.hpp>

#include <iostream>

namespace SDLFramework {

	ShaderUtil& SDLFramework::ShaderUtil::Use() {
		glUseProgram(ID);
		return *this;
	}

	void ShaderUtil::Compile(const GLchar* vertSrc, const GLchar* fragSrc, const GLchar* geomSrc) {
		GLuint vShader, fShader, gShader;

		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vertSrc, nullptr);
		glCompileShader(vShader);
		CheckCompileErrors(vShader, "VERTEX");
		
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fragSrc, nullptr);
		glCompileShader(fShader);
		CheckCompileErrors(fShader, "FRAGMENT");

		if (geomSrc != nullptr) {
			gShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(gShader, 1, &geomSrc, nullptr);
			glCompileShader(gShader);
			CheckCompileErrors(gShader, "GEOMETRY");
		}

		ID = glCreateProgram();
		glAttachShader(ID, vShader);
		glAttachShader(ID, fShader);
		if (geomSrc != nullptr)
			glAttachShader(ID, vShader);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		glDeleteShader(vShader);
		glDeleteShader(fShader);
		if (geomSrc != nullptr)
			glDeleteShader(fShader);
	}

	void ShaderUtil::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniform1f(loc, value);
	}

	void ShaderUtil::SetInteger(const GLchar* name, GLint value, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniform1i(loc, value);
	}

	void ShaderUtil::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniform2f(loc, x, y);
	}

	void ShaderUtil::SetVector2f(const GLchar* name, const glm::vec2& vec, GLboolean useShader) {
		SetVector2f(name, vec.x, vec.y, useShader);
	}

	void ShaderUtil::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniform3f(loc, x, y, z);
	}

	void ShaderUtil::SetVector3f(const GLchar* name, const glm::vec3& vec, GLboolean useShader) {
		SetVector3f(name, vec.x, vec.y, vec.z, useShader);
	}

	void ShaderUtil::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniform4f(loc, x, y, z, w);
	}

	void ShaderUtil::SetVector4f(const GLchar* name, const glm::vec4& vec, GLboolean useShader) {
		SetVector4f(name, vec.x, vec.y, vec.z, vec.w, useShader);
	}

	void ShaderUtil::SetMatrix4f(const GLchar* name, const glm::mat4& mat, GLboolean useShader) {
		if (useShader) Use();

		GLuint loc = glGetUniformLocation(ID, name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	}

	GLuint ShaderUtil::GetUniformLocation(const GLchar* name) {
		GLuint loc = glGetUniformLocation(ID, name);
		if (loc == GL_INVALID_INDEX) {
			std::cerr << "Uniform location " << name << " not found!" << std::endl;
		}
		return loc;
	}

	void ShaderUtil::CheckCompileErrors(GLuint object, std::string type) {
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (success == 0) {
				glGetShaderInfoLog(object, 1024, nullptr, infoLog);
				std::cerr << "Compile error! " << type << ":\n" << infoLog << "\n---" << std::endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (success == 0) {
				glGetProgramInfoLog(object, 1024, nullptr, infoLog);
				std::cerr << "Link error! " << type << ":\n" << infoLog << "\n---" << std::endl;
			}
		}
	}
}