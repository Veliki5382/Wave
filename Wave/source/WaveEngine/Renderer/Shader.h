#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include "WaveEngine/Core.h"


namespace wave {

	class WAVE_API Shader {

	public:
		Shader() {}
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniform4f(std::string name, const glm::mat4& VPMatrix);

	private:
		uint32_t m_ShaderProgramID;
	};

}  // namespace wave

#endif