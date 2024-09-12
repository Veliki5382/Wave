#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include "WaveEngine/Renderer/VertexBuffer.h"

namespace wave {
	
	class WAVE_API OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_BufferID;

	};



}  // namespace wave

#endif 