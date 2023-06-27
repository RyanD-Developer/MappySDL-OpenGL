#ifndef __SHADERUTIL_H
#define __SHADERUTIL_H
#include <string>

#include <glew.h>
#include <glm.hpp>

namespace SDLFramework {

	enum class ShaderType {
		Vertex,
		Fragment,
		Geometry
	};

	class ShaderUtil {
	public:
		GLuint ID;

		ShaderUtil& Use();

		void Compile(const GLchar* vertSrc, const GLchar* fragSrc, const GLchar* geomSrc = nullptr);

		void SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
		void SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);
		void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
		void SetVector2f(const GLchar* name, const glm::vec2& vec, GLboolean useShader = false);
		void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
		void SetVector3f(const GLchar* name, const glm::vec3& vec, GLboolean useShader = false);
		void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
		void SetVector4f(const GLchar* name, const glm::vec4& vec, GLboolean useShader = false);
		void SetMatrix4f(const GLchar* name, const glm::mat4& mat, GLboolean useShader = false);

		GLuint GetUniformLocation(const GLchar* name);

	private:
		void CheckCompileErrors(GLuint object, std::string type);
	};
}
#endif