#pragma once

#include "Event.h"

namespace wave {

	class WAVE_API KeyEvent : public Event {
	
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EventCategory GetEventCategory() const override { return EventCategory(int(EventCategory::Keyboard) | int(EventCategory::Input)); }

	protected:
		int m_KeyCode;

		KeyEvent(int keyCode) 
			: m_KeyCode(keyCode) {}
	};


	class WAVE_API KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(int keyCode, int repeatNumber) 
			: KeyEvent(keyCode), m_RepeatNumber(repeatNumber) {}

		inline int GetRepeatNumber() const { return m_RepeatNumber; }

		EventType GetEventType() const override { return EventType::KeyPressed; }
		const char* GetName() const override { return "KeyPressed"; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed: " << m_KeyCode << " (" << m_RepeatNumber << " times)";
			return ss.str();
		}

	private:
		int m_RepeatNumber;

	};

	class WAVE_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		EventType GetEventType() const override { return EventType::KeyReleased; }
		const char* GetName() const override { return "KeyReleased"; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released: " << m_KeyCode;
			return ss.str();
		}

	};

} // namespace wave
