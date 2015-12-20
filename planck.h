#include "input/mic.h"
 
#include <SDL.h>

class Planck {
  private:
    bool m_running = true;
    Mic m_mic;

  public:
    Planck();
    int run();

  private:

};
