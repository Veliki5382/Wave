#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "WaveEngine/Core.h"

namespace wave {


	class WAVE_API IndexBuffer {

	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);

	};


}  // namespace wave

#endif