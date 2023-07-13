#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "WaveEngine/Core.h"
#include "Event.h"

namespace wave {

	class WAVE_API WindowResizedEvent : public Event {

	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		EventCategory GetEventCategory() const override { return EventCategory::CategoryApplication; }

		static EventType GetStaticType() { return EventType::WindowResized; }
		EventType GetEventType() const override { return EventType::WindowResized; }
		const char* GetName() const override { return "WindowResized"; }
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Window Resized: (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

	private:
		unsigned int m_Width, m_Height;
	};

	class WAVE_API WindowClosedEvent : public Event {
	
	public:
		WindowClosedEvent() {}

		EventCategory GetEventCategory() const override { return EventCategory::CategoryApplication; }

		static EventType GetStaticType() { return EventType::WindowClosed; }
		EventType GetEventType() const override { return EventType::WindowClosed; }
		const char* GetName() const override { return "WindowClosed"; }
	};

	class WAVE_API AppTickEvent : public Event {
		
	public:
		AppTickEvent() {}

		EventCategory GetEventCategory() const override { return EventCategory::CategoryApplication; }

		static EventType GetStaticType() { return EventType::AppTick; }
		EventType GetEventType() const override { return EventType::AppTick; }
		const char* GetName() const override { return "AppTick"; }
	};

	class WAVE_API AppUpdateEvent : public Event {
		 
	public:
		AppUpdateEvent() {}

		EventCategory GetEventCategory() const override { return EventCategory::CategoryApplication; }

		static EventType GetStaticType() { return EventType::AppUpdate; }
		EventType GetEventType() const override { return EventType::AppUpdate; }
		const char* GetName() const override { return "AppUpdate"; }
	};
	
	class WAVE_API AppRenderEvent : public Event {

	public:
		AppRenderEvent() {}

		EventCategory GetEventCategory() const override { return EventCategory::CategoryApplication; }

		static EventType GetStaticType() { return EventType::AppRender; }
		EventType GetEventType() const override { return EventType::AppRender; }
		const char* GetName() const override { return "AppRender"; }
	};

} // namespace wave

#endif