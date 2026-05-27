#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>

#include "lib/Keypad/keypad.hpp"
#include "lib/MPU9265/gyro_manager.hpp"
#include "lib/Display/display_manager.hpp"
#include "lib/Display/gyroBall/gyroBall.hpp"
#include "lib/Display/gyroStat/gyro_stat.hpp"
#include "lib/Display/carGame/carGame.hpp"
#include "include/hw_config.hpp"

#include <vector>


MPU9250_asukiaaa gyroSensor;
DisplayManager display(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Config::OLED_RESET);
AnalogKeypad keypad(Config::ADC_BUTTON_PIN);


void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  delay(10);

  init_gyro(gyroSensor);
  display.init(Config::SCR_ADDR);
}


void loop() {
  
}