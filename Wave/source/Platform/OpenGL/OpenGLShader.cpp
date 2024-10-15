#include "wavepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace wave {

	OpenGLShader::OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc) {

		WAVE_CORE_INFO("Creating shader program.");

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			WAVE_CORE_ERROR("Vertex shader compilation failed.");
			WAVE_CORE_ASSERT(false, infoLog.data())
				// In this simple program, we'll just leave
				return;
		}
		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			WAVE_CORE_ERROR("Fragment shader compilation failed.");
			WAVE_CORE_ASSERT(false, infoLog.data())
				// In this simple program, we'll just leave
				return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ShaderProgramID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ShaderProgramID, vertexShader);
		glAttachShader(m_ShaderProgramID, fragmentShader);

		// Link our program
		glLinkProgram(m_ShaderProgramID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ShaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderProgramID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_ShaderProgramID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			WAVE_CORE_ERROR("Shader Program linking failed.");
			WAVE_CORE_ASSERT(false, infoLog.data())
				// In this simple program, we'll just leave
				return;
		}
		// Always detach shaders after a successful link.
		glDetachShader(m_ShaderProgramID, vertexShader);
		glDetachShader(m_ShaderProgramID, fragmentShader);

		WAVE_CORE_INFO("Shader program created successfully.");
	}

	void OpenGLShader::SetColor(const glm::vec4& color) {
		glUseProgram(m_ShaderProgramID);

		GLint location = glGetUniformLocation(m_ShaderProgramID, "u_Color");
		glUniform4fv(location, 1, glm::value_ptr(color));
	}

	OpenGLShader::~OpenGLShader() {

		glDeleteProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Bind() const {

		glUseProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Unbind() const {

		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform4f(std::string name, const glm::mat4& matrix) {

		glUseProgram(m_ShaderProgramID);

		GLint location = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}  // namespace wave