#pragma once

#include "zzxpch.h"
#include "ZZX/Core/Base.h"


namespace ZE
{
    // Events are currently blocking, meaning when an event occurs, the application is stopped 
    // and event immediately gets dispatched and must be dealt with right there.
    // For the future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };
    
    // use enum (instead of enum class) because we want to use EventCategory as int
    enum EventCategory
    {
        None = 0, 
        // Use BIT so that an event can be bound to multiple categories 
        EventCategoryApplication	= BIT(0), // 0000 0001
        EventCategoryInput			= BIT(1), // 0000 0010
        EventCategoryKeyboard		= BIT(2), // 0000 0100
        EventCategoryMouse			= BIT(3), // 0000 1000
        EventCategoryMouseButton	= BIT(4), // 0001 0000
    };

    // These macros are created to save typing :)
    // GetStaticType is used for checking the type of an event in run time
    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                                   virtual EventType GetEventType() const override { return GetStaticType(); }\
                                   virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;
        // We want to control whether to "consume" the events so that it can't propagate further
        // m_Handled = true to consume the event
        bool m_Handled = false;

        // virtual because we need to get the event type of a generic Event
        virtual EventType GetEventType() const = 0;
        // for debugging purpose
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        // This is the default behavior. Override this if you want more details
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    // This class is for dispatching events based on its type
    class EventDispatcher
    {
        // a function takes in T (any events) reference and returns bool
        // return true to "consume" the input
        // 
        // This is normally implemented in the same class as where you handle the event
        // e.g. bool Application::OnWindowClosed in Applicaiton class
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {}

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                // cast m_Event addr to T pointer, and dereference it 
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    // logging purpose so we use << on events
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}
