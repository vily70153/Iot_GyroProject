#ifndef KEYPAD_HPP
#define KEYPAD_HPP


enum class ButtonPosition {
    FREE, MID, UP, DOWN, LEFT, RIGHT, UNKNOWN
};

struct Range {
    int minVal;
    int maxVal;
    bool contains(int val) const {
        return val >= minVal && val <= maxVal;
    }
};

constexpr Range POS_DOWN  = { 2600, 5000 };
constexpr Range POS_RIGHT = { 2450, 2550 };
constexpr Range POS_UP    = { 1650, 1750 };
constexpr Range POS_LEFT  = { 1100, 1200 };
constexpr Range POS_MID   = { 750, 850 };
constexpr Range POS_FREE  = { 0, 100 };

class AnalogKeypad {
private:
    int pin;
    ButtonPosition currentState;
    ButtonPosition lastReading;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50;

    ButtonPosition determinePosition(int adcVal) const;

public:
    AnalogKeypad(int adcPin) : pin(adcPin), currentState(ButtonPosition::FREE), lastReading(ButtonPosition::FREE), lastDebounceTime(0) {}

    void update();

    ButtonPosition getCurrentBtnState() const;
    const char* positionToString(ButtonPosition btnPos);
};

#endif