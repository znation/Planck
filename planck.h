#include "input/mic.h"
#include "ui/ui.h"
 
#include <SDL.h>

class Planck {
  private:
    bool m_running = true;
    Mic m_mic;
    UI m_ui;

  public:
    int run();
};
