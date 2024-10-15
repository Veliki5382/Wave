#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <glm/glm.hpp>

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/Shader.h"

namespace wave {

	class WAVE_API OpenGLShader : public Shader {

	public:
		OpenGLShader() {}
		OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniform4f(std::string name, const glm::mat4& VPMatrix) override;
		virtual void SetColor(const glm::vec4& color) override;

	private:
		uint32_t m_ShaderProgramID;
	};

}  // namespace wave

#endif