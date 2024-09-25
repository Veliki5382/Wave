#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "WaveEngine/Core.h"
#include "BufferLayout.h"

namespace wave {

	class WAVE_API VertexBuffer {

	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	
	};

}  // namespace wave


#endif
