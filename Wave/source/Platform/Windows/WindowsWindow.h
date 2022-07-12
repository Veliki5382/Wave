#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "wavepch.h"

namespace wave {

	class WAVE_API WindowsWindow {

	public:
		WindowsWindow() {}





	private:
		
		struct WindowData {
			std::string m_Title;
			unsigned int m_Width, m_Heigth;
			bool VSync;
		};

	};

}



#endif