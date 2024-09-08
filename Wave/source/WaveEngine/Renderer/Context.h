#ifndef CONTEXT_H
#define CONTEXT_H

#include "WaveEngine/Core.h"

namespace wave {

	class WAVE_API Context {

	public:
		
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};


} // namespace wave


#endif
