/*

Event system for QEngine

*/
#pragma once
#include <vector>
#include <functional>
#include <algorithm>


namespace QEngine {

template<typename...>
class Event;

template<typename... T>
class EventConnection {
public:
    void disconnect() {
        m_ParentEvent.disconnectConnection(this);
    }


    friend class Event<T...>;


private:
    EventConnection(
        Event<T...>& parentEvent,
        std::function<void(T...)> function,
        bool disconnectAfterFired
    ) : m_ParentEvent(parentEvent), m_Function(function),
        m_DisconnectAfterFired(disconnectAfterFired) {}


    Event<T...>& m_ParentEvent;
    std::function<void(T...)> m_Function;
    bool m_DisconnectAfterFired;
};


template<typename...>
class BindableEvent;

template<typename... T>
class Event {
public:
    EventConnection<T...>* connect(std::function<void(T...)> function) {
        EventConnection<T...>* eventConnection = new EventConnection<T...>(*this, function, false);

        m_EventConnections.push_back(eventConnection);
        return eventConnection;
    }

    EventConnection<T...>* once(std::function<void(T...)> function) {
        EventConnection<T...>* eventConnection = new EventConnection<T...>(*this, function, true);

        m_EventConnections.push_back(eventConnection);
        return eventConnection;
    }


    friend class EventConnection<T...>;
    friend class BindableEvent<T...>;


private:
    Event() {}
    ~Event() {
        for (auto eventConnection : m_EventConnections) {
            delete eventConnection;
        }

        m_EventConnections.clear();
    }


    void fire(T... args) {
        auto it = m_EventConnections.begin();

        while (it != m_EventConnections.end()) {
            ((*it)->m_Function)(args...);

            if ((*it)->m_DisconnectAfterFired) {
                disconnectConnection(*it);
            } else {
                ++it;
            }
        }
    }


    void disconnectConnection(EventConnection<T...>* eventConnection) {
        m_EventConnections.erase(
            std::remove(m_EventConnections.begin(), m_EventConnections.end(), eventConnection),
            m_EventConnections.end()
        );

        delete eventConnection;
    }


    std::vector<EventConnection<T...>*> m_EventConnections;
};


template<typename... T>
class BindableEvent {
public:
    Event<T...> event;

    void fire(T... args) {
        event.fire(args...);
    }
};

}
