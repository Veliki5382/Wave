#ifndef SHADER_H
#define SHADER_H

#include "WaveEngine/Core.h"

namespace wave {

	class WAVE_API Shader {

	public:
		Shader() {}
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_ShaderProgramID;
	};

}  // namespace wave

#endif