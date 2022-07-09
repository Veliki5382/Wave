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
		invalid		=	0,
		Application	=	WAVE_BIT(0),
		Input		=	WAVE_BIT(1),
		Keyboard	=	WAVE_BIT(2),
		Mouse		=	WAVE_BIT(3),
		MouseButton =	WAVE_BIT(4)
	};

	class WAVE_API Event {
		friend class EventDispatcher;

	public:
		Event() {}
		~Event() {}

		virtual EventType GetEventType() const;
		virtual const char* GetName() const;
		virtual EventCategory GetEventCategory() const;
		virtual std::string ToString() const { return GetName(); }

		bool InCategory(EventCategory category) {
			return GetEventCategory() & category;
		}

	protected:
		bool m_Handled = false;

	};


	class EventDispatcher {
		
		template<typename T>
		using EventFunction = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunction<T> func) {
			if (m_Event.GetEventType() == T::GetEventType()) {
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
