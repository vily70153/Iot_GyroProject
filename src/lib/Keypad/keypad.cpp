#include "keypad.hpp"

#include <Arduino.h>

ButtonPosition AnalogKeypad::determinePosition(int adcVal) const {
    if ( POS_FREE.contains(adcVal) )  return ButtonPosition::FREE;
    if ( POS_MID.contains(adcVal) )   return ButtonPosition::MID;
    if ( POS_LEFT.contains(adcVal) )  return ButtonPosition::LEFT;
    if ( POS_RIGHT.contains(adcVal) ) return ButtonPosition::RIGHT;
    if ( POS_DOWN.contains(adcVal) )  return ButtonPosition::DOWN;
    if ( POS_UP.contains(adcVal) )    return ButtonPosition::UP;
    return ButtonPosition::UNKNOWN;
}

void AnalogKeypad::update() {
    int adcVal = analogRead(pin);
    ButtonPosition newBtnPos = determinePosition(adcVal);
    
    if (newBtnPos != lastReading) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (newBtnPos != currentState) {
        currentState = newBtnPos;
      }
    }
    lastReading = newBtnPos; 
}

ButtonPosition AnalogKeypad::getCurrentBtnState() const {
    return currentState;
}

const char* AnalogKeypad::positionToString(ButtonPosition btnPos) {
  switch (btnPos) {
    case ButtonPosition::FREE:    return "FREE";
    case ButtonPosition::UP:      return "UP";
    case ButtonPosition::DOWN:    return "DOWN";
    case ButtonPosition::LEFT:    return "LEFT";
    case ButtonPosition::RIGHT:   return "RIGHT";
    case ButtonPosition::MID:     return "MID";
    case ButtonPosition::UNKNOWN: return "UNKNOWN";
    default:                      return "INVALID";
  }
}