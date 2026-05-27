#include "display_manager.hpp"
#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


bool DisplayManager::init(uint8_t screen_addr) {
  if (!oled.begin(SSD1306_SWITCHCAPVCC, screen_addr)) {
    Serial.println("ERR: oled initialization failed!");
    return false;
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.display();

  return true;
}

void DisplayManager::clear() {
  oled.clearDisplay();
}

void DisplayManager::render() {
  oled.display();
}

void DisplayManager::draw_text(int16_t x, int16_t y, const char* text, bool inverted) {
  oled.setCursor(x, y);
  if (inverted) oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  else oled.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  oled.print(text);
}

void DisplayManager::drawSprite(int16_t x, int16_t y, const unsigned char* bitmap, uint8_t w, uint8_t h) {
  oled.drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);
}

void DisplayManager::draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  oled.drawLine(x0, y0, x1, y1, WHITE);
}

void DisplayManager::draw_circle(int16_t x, int16_t y, int16_t radius, bool is_fill) {
  if (is_fill) oled.fillCircle(x, y, radius, WHITE);
  else oled.drawCircle(x, y, radius, WHITE);
}

void DisplayManager::drawHeart(int x, int y) {
  // Рисуем маленькое заполненное сердечко 7x7 пикселей
  oled.drawPixel(x+1, y, WHITE); oled.drawPixel(x+2, y, WHITE);
  oled.drawPixel(x+4, y, WHITE); oled.drawPixel(x+5, y, WHITE);
  
  oled.drawFastHLine(x, y+1, 7, WHITE);
  oled.drawFastHLine(x, y+2, 7, WHITE);
  oled.drawFastHLine(x+1, y+3, 5, WHITE);
  oled.drawFastHLine(x+2, y+4, 3, WHITE);
  
  oled.drawPixel(x+3, y+5, WHITE);
}

Adafruit_SSD1306& DisplayManager::get_oled() {
  return oled;
}