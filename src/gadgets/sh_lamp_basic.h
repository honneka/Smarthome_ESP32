#ifndef __SH_Lamp_Basic__
#define __SH_Lamp_Basic__

#include "sh_lamp.h"
#include <Arduino.h>

class SH_Lamp_Basic : public SH_Lamp {
private:

  uint8_t pin;

  bool default_state;

public:

  explicit SH_Lamp_Basic(JsonObject);

  void refresh() override;
};

#endif