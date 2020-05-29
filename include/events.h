#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <mutex>
#include <map>

enum EventType {
    EVENT_QUIT,
    EVENT_STOP_AUDIO,
    EVENT_NOEVENT
};

class EventProducer {
private:
    std::mutex* queue_mutex;
public:
    EventProducer(std::mutex* m){ queue_mutex = m; };
    virtual void ThrowEvent(EventType e) = 0;
    virtual ~EventProducer(){};
};

class Observer {
public:
    virtual void CatchEvent(EventType e) = 0;
    virtual ~Observer(){};
};

class SimpleObserver : Observer {
public:
    SimpleObserver(){};
    virtual void CatchEvent(EventType e) override;
};

class EventHandler {
    typedef std::vector<Observer*> ObserverList; 
    typedef std::map<EventType, ObserverList> ObserversTable;

private:
    std::mutex queue_mutex;
    std::vector<EventType> event_queue;
    bool should_quit = false;
    ObserversTable observer_connections;
    SimpleObserver quit_notifier;
public:
    EventHandler(){};
    bool ShouldQuit(void);
    bool TriggerEvent(EventType e);
    // bool Connect(EventType e, Observer& o);
    void ProcessEvents(void);
    EventType GetNextEvent(void);
};

#endif // EVENTS_H

