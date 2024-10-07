#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

#include "WaveEngine/Core.h"

namespace wave {

	class WAVE_API Time {
	
	public:
		Time(float time = 0.0f)
			: m_CurrentTime(time) {}

		operator float() const { return m_CurrentTime; }

		void UpdateTime() { m_CurrentTime = (float)glfwGetTime(); }
		inline float GetDeltaTime() const { return m_DeltaTime; }
		inline void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }
		inline float GetTime() const { return m_CurrentTime; }

	private:
		float m_CurrentTime, m_DeltaTime;
	};

}  //namespace wave

#endif