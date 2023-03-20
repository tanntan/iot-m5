#include <M5Stack.h>

namespace LTLabs {
  namespace Screen {
    void begin() {
      M5.begin();
      M5.Power.begin();
      M5.Lcd.begin();
      M5.Lcd.clear(WHITE);
    }
  }
}
