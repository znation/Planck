#include "input.h"
#include "inputsource.h"

class InputManager {
  private:
    std::shared_ptr<Input> m_input;

  public:
    InputManager(InputSource initialSource);
    void setInputSource(InputSource source);
    std::shared_ptr<Input> operator->() const;
};
