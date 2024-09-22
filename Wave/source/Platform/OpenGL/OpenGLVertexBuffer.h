#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include "WaveEngine/Renderer/VertexBuffer.h"
#include "WaveEngine/Renderer/BufferLayout.h"

namespace wave {
	
	class WAVE_API OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_BufferID;
		BufferLayout m_Layout;
	};


}  // namespace wave

#endif 