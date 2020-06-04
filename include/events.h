#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <mutex>
#include <map>
#include <string>

enum EventType {
    EVENT_QUIT,
    EVENT_STOP_AUDIO,
    EVENT_AUDIO_DATA_READY,
    EVENT_NOEVENT
};

struct Event {
    EventType e;
    std::string message;
};

class Observer {
public:
    virtual void CatchEvent(EventType e) = 0;
    virtual ~Observer(){};
};

class EventHandler {
    typedef std::vector<Observer*> ObserverList; 
    typedef std::map<EventType, ObserverList> ObserversTable;
    typedef struct{std::mutex data_access; 
                    std::mutex next_to_access; 
                    std::mutex low_priority;} TripleMutex;

private:
    TripleMutex queue_mutex;
    std::vector<EventType> event_queue;
    bool should_quit = false;
    ObserversTable observer_connections;
public:
    EventHandler(){};
    bool ShouldQuit(void);
    bool TriggerEvent(EventType e);
    bool Connect(EventType e, Observer& o);
    void ProcessEvents(void);
    EventType GetNextEvent(void);
};

#endif // EVENTS_H

