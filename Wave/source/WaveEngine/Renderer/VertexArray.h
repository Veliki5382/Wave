#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Renderer/VertexBuffer.h"
#include "WaveEngine/Renderer/IndexBuffer.h"

namespace wave {

	class WAVE_API VertexArray {

	public:
		VertexArray() {}
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		static VertexArray* Create();

	};


}  // namespace wave

#endif