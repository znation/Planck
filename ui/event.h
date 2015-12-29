#ifndef _events_h
#define _events_h

#include <SDL.h>

#include <functional>
#include <unordered_map>

class Event {
  private:
    static std::unordered_multimap<size_t, std::function<void(const SDL_Event&)>> m_handlers;

  public:
    static void observe(SDL_EventType eventType, std::function<void(const SDL_Event&)> callback);
    static void send(const SDL_Event& event);
};

#endif
