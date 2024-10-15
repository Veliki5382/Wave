#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include "WaveEngine/Core.h"


namespace wave {

	class WAVE_API Shader {

	public:
		Shader() {}
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetColor(const glm::vec4& color) = 0;
		virtual void UploadUniform4f(std::string name, const glm::mat4& VPMatrix) = 0;

		static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);
	};

}  // namespace wave

#endif