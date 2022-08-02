#ifndef KEY_EVENT_H
#define KEY_EVENT_H

//#include "source/wavepch.h"
#include "Event.h"

namespace wave {

	class WAVE_API KeyEvent : public Event {
	
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EventCategory GetEventCategory() const override {
			return EventCategory(int(EventCategory::CategoryKeyboard) | int(EventCategory::CategoryInput));
		}

	protected:
		int m_KeyCode;

		KeyEvent(int keyCode) 
			: m_KeyCode(keyCode) {}
	};


	class WAVE_API KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(int keyCode, int repeatNumber) 
			: KeyEvent(keyCode), m_Repeat(repeatNumber) {}

		inline int GetRepeatNumber() const { return m_Repeat; }

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return EventType::KeyPressed; }
		const char* GetName() const override { return "KeyPressed"; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed: " << m_KeyCode << " (" << m_Repeat << " times)";
			return ss.str();
		}

	private:
		int m_Repeat;

	};

	class WAVE_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return EventType::KeyReleased; }
		const char* GetName() const override { return "KeyReleased"; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}

	};

} // namespace wave

#endif