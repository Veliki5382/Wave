#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/VertexArray.h"

namespace wave {

	class WAVE_API OpenGLVertexArray : public VertexArray {

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() override { return m_VertexBuffers; }
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() override { return m_IndexBuffer; }


	private:
		uint32_t m_VertexArrayID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};


}  // namespace wave

#endif