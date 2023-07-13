#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "WaveEngine/Core.h"
#include "Event.h"

namespace wave {

	class WAVE_API MouseEvent : public Event {
	
	public:
		EventCategory GetEventCategory() const override {
			return EventCategory(int(EventCategory::CategoryMouse) | int(EventCategory::CategoryInput));
		}

	protected:
		MouseEvent() {}

	};

	class WAVE_API MouseMovedEvent : public MouseEvent {

	public:
		MouseMovedEvent(double x, double y) 
			: m_MouseX(x), m_MouseY(y) {}

		inline double GetX() const { return m_MouseX; }
		inline double GetY() const { return m_MouseY; }

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return EventType::MouseMoved; }
		const char* GetName() const override { return "MouseMoved"; }
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse move: (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

	private:
		double m_MouseX, m_MouseY;
	};

	class WAVE_API MouseScrolledEvent : public MouseEvent {

	public:
		MouseScrolledEvent(double xOffset, double yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline double GetXOffset() const { return m_XOffset; }
		inline double GetYOffset() const { return m_YOffset; }


		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return EventType::MouseScrolled; }
		const char* GetName() const override { return "MouseScrolled"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse scrolled: (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

	private:
		double m_XOffset, m_YOffset;
	};

	class WAVE_API MouseButtonEvent : public Event {
	
	public:
		inline int GetMouseButtonCode() const { return m_MouseButtonCode; }
		
		EventCategory GetEventCategory() const override {
			return EventCategory(int(EventCategory::CategoryMouseButton) | int(EventCategory::CategoryInput));
		}

	protected:
		int m_MouseButtonCode;
		
		MouseButtonEvent(int mouseButtonCode)
			: m_MouseButtonCode(mouseButtonCode) {}
	};

	class WAVE_API MouseButtonPressedEvent : public MouseButtonEvent {
	
	public:
		MouseButtonPressedEvent(int mouseButtonCode)
			: MouseButtonEvent(mouseButtonCode) {}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return EventType::MouseButtonPressed; }
		const char* GetName() const override { return "MouseButtonPressed"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button pressed: " << m_MouseButtonCode;
			return ss.str();
		}
	};

	class WAVE_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int mouseButtonCode)
			: MouseButtonEvent(mouseButtonCode) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return EventType::MouseButtonReleased; }
		const char* GetName() const override { return "MouseButtonReleased"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button released: " << m_MouseButtonCode;
			return ss.str();
		}
	};

} // namespace wave

#endif