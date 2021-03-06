#ifndef WINDOW_H
#define WINDOW_H

#include "wavepch.h"

#include "Core.h"

namespace wave {

	struct WindowProps {
		std::string Title;
		unsigned int Height, Width;

		WindowProps(std::string title = "Wave Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Height(height), Width(width) {}
	};

	class WAVE_API Window {

	public:
		virtual ~Window() {}

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;
		
		virtual bool VSyncStatus() const = 0;
		virtual void SetVSync(bool status) = 0;

		virtual void OnUpdate() = 0;

		static Window* Create(WindowProps& props = WindowProps());

	};
	

}


#endif 
