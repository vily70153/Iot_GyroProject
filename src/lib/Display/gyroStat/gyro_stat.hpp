#ifndef  GYRO_STAT_HPP
#define GYRO_STAT_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>
#include "lib/Display/display_manager.hpp"  



void gyro_stat(DisplayManager& display, MPU9250_asukiaaa& gyroSensor);



#endif