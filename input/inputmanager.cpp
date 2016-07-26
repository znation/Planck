#include "inputmanager.h"

static std::shared_ptr<Input> getInput(InputSource source) {
  switch (source) {
    case InputSource::Microphone:
      return std::make_shared<Mic>();
    default:
      assert(False);
  }
}

InputManager::InputManager(InputSource initialSource) :
 m_input(getInput(initialSource)) 
{}

std::shared_ptr<Input> InputManager::operator->() const {
  assert(m_input != nullptr);
  return m_input;
}
