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


enum class GameState {
  MENU,
  GYRO_BALL,
  GYRO_STAT,
  CAR_GAME
};

GameState currentState = GameState::MENU;

int menuIndex = 0; 

unsigned long buttonPressedTime = 0;
bool isButtonPressed = false;
bool longPressTriggered = false;
const unsigned long LONG_PRESS_MS = 800;

ButtonPosition lastProcessedState = ButtonPosition::FREE;

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  delay(100);

  init_gyro(gyroSensor);
  display.init(Config::SCR_ADDR);
}


void loop() {
  keypad.update();
  ButtonPosition btn = keypad.getCurrentBtnState();

  if (btn != ButtonPosition::FREE) {
    if (!isButtonPressed) {
      isButtonPressed = true;
      buttonPressedTime = millis();
      longPressTriggered = false;
    } else if (!longPressTriggered && (millis() - buttonPressedTime >= LONG_PRESS_MS)) {
      longPressTriggered = true;
      
      if (currentState != GameState::MENU) {
        currentState = GameState::MENU;
        delay(300); 
      }
    }
  } else {
    isButtonPressed = false;
    longPressTriggered = false;
  }

  switch (currentState) {
    
    case GameState::MENU: {
      if (btn != lastProcessedState) {
        if (btn == ButtonPosition::DOWN || btn == ButtonPosition::RIGHT) {
          menuIndex = (menuIndex + 1) % 3;
        } 
        else if (btn == ButtonPosition::UP || btn == ButtonPosition::LEFT) {
          menuIndex = (menuIndex - 1 + 3) % 3;
        } 
        else if (btn == ButtonPosition::MID) {
          if (menuIndex == 0) currentState = GameState::GYRO_BALL;
          else if (menuIndex == 1) currentState = GameState::GYRO_STAT;
          else if (menuIndex == 2) currentState = GameState::CAR_GAME;
          delay(200);
        }
        lastProcessedState = btn;
      }

      display.clear();
      display.get_oled().setTextSize(1);
      display.get_oled().setTextColor(SSD1306_WHITE);
      display.get_oled().setCursor(10, 10);

      if (menuIndex == 0) {
      }
      
      

      display.get_oled().print(menuIndex == 0 ? "> 1. GYRO BALL" : "  1. GYRO BALL");
      display.get_oled().setCursor(10, 30);
      display.get_oled().print(menuIndex == 1 ? "> 2. GYRO STAT" : "  2. GYRO STAT");
      display.get_oled().setCursor(10, 50);
      display.get_oled().print(menuIndex == 2 ? "> 3. CAR GAME" : "  3. CAR GAME");
      
      display.render();
      break;
    }

    case GameState::GYRO_BALL:
      gyro_ball(display, gyroSensor);
      break;

    case GameState::GYRO_STAT:
      gyro_stat(display, gyroSensor);
      break;

    case GameState::CAR_GAME:
      car_game(gyroSensor, display); 
      break;
  }
}