#ifndef EVENT_H
#define EVENT_H

#include "wavepch.h"

#include "WaveEngine/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // for OStream overriding


namespace wave {

	// EventSystem is currently stopping Application,
	// need to implement multi-thread system so it can
	// run parrarel to application.


	enum class EventType {
		invalid = 0,
		WindowClosed, WindowResized, WindowFocused, WindowUnfocused, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyTyped, KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled,
		MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory {
		invalid = 0,
		CategoryApplication = WAVE_BIT(0),
		CategoryInput = WAVE_BIT(1),
		CategoryKeyboard = WAVE_BIT(2),
		CategoryMouse = WAVE_BIT(3),
		CategoryMouseButton = WAVE_BIT(4)
	};

	class WAVE_API Event {
		friend class EventDispatcher;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Event& e) {

			return os << e.ToString();
		}

	public:
		Event() {}
		~Event() {}

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual EventCategory GetEventCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool InCategory(EventCategory category) {
			return GetEventCategory() & category;
		}

		bool Handled() const { return m_Handled; }

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


	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		
		return os << e.ToString();
	}



} // namespace wave

#endif