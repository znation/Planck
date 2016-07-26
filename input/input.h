#include "../frame.h"

#include <portaudio.h>

class Input {
  protected:
    Input();

  public:
    virtual ~Input();
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    Input(const Input&&) = delete;
    Input& operator=(const Input&&) = delete;
    virtual TimeDomainFrame sample() const = 0;
};
