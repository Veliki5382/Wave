#pragma once

#include <string>
#include <functional>

namespace wave {

	// EventSystem is currently stopping Application,
	// need to implement multi-thread system so it can
	// run parrarel to application.

	
	enum class EventType {
		invalid = 0,
		WindowClosed, WindowResized, WindowFocused, WindowUnfocused, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled,
		MouseButtonPressed, MouseButtonReleased
	};
	
	enum EventCategory {
		invalid					=	0,
		CategoryApplication		=	WAVE_BIT(0),
		CategortyInput			=	WAVE_BIT(1),
		CategortyKeyboard		=	WAVE_BIT(2),
		CategortyMouse			=	WAVE_BIT(3),
		CategortyMouseButton	=	WAVE_BIT(4)
	};
	
	class WAVE_API Event {
		friend class EventDispatcher;

	public:
		Event() {}
		~Event() {}

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0 ;
		virtual EventCategory GetEventCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool InCategory(EventCategory category) {
			return GetEventCategory() & category;
		}

	protected:
		bool m_Handled = false;

	};


	class WAVE_API EventDispatcher {
		
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunction<T> func) {
				if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			else {
				return false;
			}
		}

	private:
		Event& m_Event;

	};
	
} // namespace wave
