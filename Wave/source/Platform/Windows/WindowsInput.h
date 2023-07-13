#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include "WaveEngine/Core.h"
#include "WaveEngine/Input.h"

namespace wave {


	class WAVE_API WindowsInput : public Input {

	private:
		inline bool GetKeyStateImpl(int keycode) override;
		bool GetMouseButtonStateImpl(int button) override;
		std::pair<double, double> GetMousePositionImpl() override;
		double GetMouseXPosImpl() override;
		double GetMouseYPosImpl() override;
		double GetScrollXOffsetImpl() override;
		double GetScrollYOffsetImpl() override;
		int GetWindowWidthImpl() override;
		int GetWindowHeightImpl() override;
	};


} // namespace wave

#endif
