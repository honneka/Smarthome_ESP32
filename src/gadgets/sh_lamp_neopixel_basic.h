#ifndef __SH_Lamp_NeoPixel_Basic__
#define __SH_Lamp_NeoPixel_Basic__

#include "sh_lamp.h"
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include <NeoPixelBus.h>

#ifdef __AVR__

#include <avr/power.h>

#endif

class SH_Lamp_NeoPixel_Basic : public SH_Lamp {
private:
  uint8_t pin;
  uint16_t len;
  Adafruit_NeoPixel* led_stripe;

public:

  explicit SH_Lamp_NeoPixel_Basic(JsonObject gadget) :
    SH_Lamp(gadget, CLR_BRI) {
    if (gadget["length"] != nullptr) {
      len = gadget["length"].as<uint16_t>();
      logger.print("Length: ");
      logger.addln(len);
    } else {
      len = 1;
      logger.println(LOG_ERR, "No Length selected.");
    }
    if (gadget["pin"] != nullptr) {
      pin = gadget["pin"].as<uint8_t>();
      logger.print("Pin: ");
      logger.addln(pin);

      led_stripe = new Adafruit_NeoPixel(len, pin, NEO_GRB + NEO_KHZ800);
      led_stripe->begin();
      led_stripe->clear();
      led_stripe->show();
    } else {
      pin = 0;
      logger.println(LOG_ERR, "No Pin selected.");
    }
  };

  void refresh() override {
    if (has_changed) {
      logger.print(getName(), "has changed.\n");
      auto clr = lamp_color.getRGB();

      setLEDColor(clr->getRed(), clr->getGreen(), clr->getBlue());
    }
    has_changed = false;
  };

  void setLEDColor(int r, int g, int b) {
    Serial.printf("[%s] Setting Color: (%d, %d, %d)\n", getName(), r, g, b);

    for (int k = 0; k < len; k++) {
      led_stripe->setPixelColor(k, Adafruit_NeoPixel::Color(r, g, b));
    }
    led_stripe->show();
  }
};

#endif