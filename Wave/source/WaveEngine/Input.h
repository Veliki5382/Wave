#ifndef INPUT_H
#define INPUT_H

#include "WaveEngine/Core.h"

namespace wave {

	class WAVE_API Input {

	public:
		inline static bool GetKeyState(int keycode) { return s_Instance->GetKeyStateImpl(keycode); }
		inline static bool GetMouseButtonState(int button) { return s_Instance->GetMouseButtonStateImpl(button); }
		inline static std::pair<double, double> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static double GetMouseXPos() { return s_Instance->GetMouseXPosImpl(); }
		inline static double GetMouseYPos() { return s_Instance->GetMouseYPosImpl(); }
		inline static double GetScrollXOffset() { return s_Instance->GetScrollXOffsetImpl(); }
		inline static double GetScrollYOffset() { return s_Instance->GetScrollYOffsetImpl(); }
		inline static int GetWindowWidth() { return s_Instance->GetWindowWidthImpl(); }
		inline static int GetWindowHeight() { return s_Instance->GetWindowHeightImpl(); }

	protected:
		virtual bool GetKeyStateImpl(int keycode) = 0;
		virtual bool GetMouseButtonStateImpl(int button) = 0;
		virtual std::pair<double, double> GetMousePositionImpl() = 0;
		virtual double GetMouseXPosImpl() = 0;
		virtual double GetMouseYPosImpl() = 0;
		virtual double GetScrollXOffsetImpl() = 0;
		virtual double GetScrollYOffsetImpl() = 0;
		virtual int GetWindowWidthImpl() = 0;
		virtual int GetWindowHeightImpl() = 0;

	protected:
		static Input* s_Instance;
	};


} // namespace wave

#endif 