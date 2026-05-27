#ifndef CAR_GAME_HPP
#define CAR_GAME_HPP

#include <vector>

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
#include "include/hw_config.hpp"

  
  void car_game(MPU9250_asukiaaa& gyroSensor, DisplayManager& display);


#endif