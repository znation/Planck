#include "input/inputmanager.h"
#include "ui/ui.h"
 
#include <SDL.h>

class Planck {
  private:
    bool m_running = true;
    InputManager m_inputManager;
    UI m_ui;

  public:
    int run();
};
