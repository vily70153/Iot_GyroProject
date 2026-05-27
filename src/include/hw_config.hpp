#ifndef HW_CONFIG_HPP
#define HW_CONFIG_HPP

#include <cstdint>

namespace Config {
    constexpr uint8_t PIN_KEYPAD = 3;
    constexpr uint8_t PIN_SDA    = 4;
    constexpr uint8_t PIN_SCL    = 5;

    constexpr uint8_t ADC_BUTTON_PIN = 0;
    constexpr uint8_t BUZZER_PIN =     1;


    constexpr uint8_t SCREEN_WIDTH  = 128;
    constexpr uint8_t SCREEN_HEIGHT = 64;
    constexpr uint8_t SCR_ADDR      = 0x3C;
    constexpr int8_t  OLED_RESET    = -1;

    constexpr uint32_t SERIAL_BAUD_RATE = 115200;

    constexpr int CENTER_X = 64;
    constexpr int CENTER_Y = 32;
    constexpr float SENSITIVITY = 0.6;
    constexpr float SMOOTHING = 0.15;
}

#endif