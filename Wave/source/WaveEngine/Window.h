#ifndef WINDOW_H
#define WINDOW_H

#include "wavepch.h"

namespace wave {

	struct WindowProps {
		std::string Title;
		unsigned int Height, Width;

		WindowProps(std::string title = "Wave Engine",
					unsigned int height = 720,
					unsigned int width = 1280)
			: Title("Wave Engine"), Height(height), Width(width) {}
	};

	class WAVE_API Window {

	public:
		
		virtual ~Window() = 0;

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;
		
		virtual bool VSyncStatus() const = 0;
		virtual void SetVSync(bool status) = 0;

		static Window* Create(WindowProps wps = WindowProps());

	};
	

}


#endif 
