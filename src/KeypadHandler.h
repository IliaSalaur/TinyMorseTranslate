#ifndef MY_KEYPAD_HANDLER_H
#define MY_KEYPAD_HANDLER_H

#include <Arduino.h>
#include <functional>

const size_t k_hold_period = 400;
const size_t k_click_debounce = 70;

enum class EventsEnum
{
  IDLE = 0,
  CLICK = 'c',
  DOUBLE = 'd',
  HOLD = 'h'
};

class ExtendedButton
{
private:
  uint8_t pin;

  uint32_t clickDebounce;
  uint32_t holdTimer;
  EventsEnum lastEvent;
  bool keyState;

  std::function<void(EventsEnum)> eventListener; 

public:
  ExtendedButton(uint8_t pin_)
      : 
        pin{pin_},
        clickDebounce(0),
        holdTimer(0),
        lastEvent(EventsEnum::IDLE),
        keyState{false},
        eventListener{nullptr}
  {
    pinMode(pin, INPUT_PULLUP);
  }

  void handle()
  {
    static uint8_t count = 0;

    if (millis() - clickDebounce > k_click_debounce)
    {
      if (!digitalRead(pin) && !keyState)
      {
        keyState = true;
        holdTimer = millis();
      }
      else if (keyState && digitalRead(pin))
      {
        if (millis() - holdTimer > k_hold_period)
        {
          Serial.printf("Hold\n");
          lastEvent = EventsEnum::HOLD;
        }
        else{
          lastEvent = EventsEnum::CLICK;
          Serial.printf("Click\n");            
        }

        Serial.printf("Event: %c;\n", char(lastEvent));
        if (eventListener)
          eventListener(lastEvent);

        lastEvent = EventsEnum::IDLE;
        clickDebounce = millis();
        keyState = false;
      }
    }
  }

  void addEventListener(std::function<void(EventsEnum)> cb)
  {
    eventListener = cb;
  }
};

#endif