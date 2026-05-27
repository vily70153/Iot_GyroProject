#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class DisplayManager {
private:
    Adafruit_SSD1306 oled;
public:
    DisplayManager(uint8_t w, uint8_t h, int8_t reset_pin)
        : oled(w, h, &Wire, reset_pin) {}

    bool init(uint8_t i2c_addr);
    void clear();
    void render();

    void draw_circle(int16_t x, int16_t y, int16_t radius, bool is_fill);
    void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void draw_text(int16_t x, int16_t y, const char* text, bool inverted = false);
    void drawHeart(int x, int y);
    void drawSprite(int16_t x, int16_t y, const unsigned char* bitmap, uint8_t w, uint8_t h);
};


#endif