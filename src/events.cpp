#include "events.h"
#include <mutex>
#include <condition_variable>

// bool EventHandler::TriggerEvent(EventType e) {
//     std::unique_lock<std::mutex> lock(this->queue_mutex);
//     this->event_queue.push_back(e);
// }

// bool EventHandler::Connect(EventType e, Observer& o) {
//     this->observer_connections[e].push_back(o);
//     return true;
// }

void SimpleObserver::CatchEvent(EventType e) {
    return;
}

void EventHandler::ProcessEvents(void) {
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    while (!this->event_queue.empty()) {
        EventType e = this->event_queue.back();
        this->event_queue.pop_back();
        if (e == EventType::EVENT_QUIT) {
            this->should_quit = true;
            return;
        }
        ObserverList& observers = this->observer_connections[e];
        for (int i=0; i<observers.size(); i++) {
            Observer* current_observer = observers[i];
            current_observer->CatchEvent(e);
        }
    }
}

EventType EventHandler::GetNextEvent(void) {
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    if (!this->event_queue.empty()) {
        EventType e = this->event_queue.back();
        this->event_queue.pop_back();
        return e;
    }
    return EventType::EVENT_NOEVENT;
}

bool EventHandler::ShouldQuit(void) {
    return this->should_quit;
}