#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "WaveEngine/Core.h"
#include "Renderer.h"

namespace wave {

	class WAVE_API VertexBuffer {

	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	
	};

}  // namespace wave


#endif
