#include "event.h"

std::unordered_multimap<size_t, std::function<void(const SDL_Event&)>> Event::m_handlers;

void Event::observe(SDL_EventType eventType, std::function<void(const SDL_Event&)> callback) {
  m_handlers.insert(std::pair<const size_t, std::function<void(const SDL_Event&)>>(eventType, callback));
}

void Event::send(const SDL_Event& event) {
  auto search = m_handlers.find(event.type);
  while (search != m_handlers.end()) {
    search->second(event);
    search++;
  }
}
