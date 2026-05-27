#ifndef GYROBALL_HPP
#define GYROBALL_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>
#include "lib/Display/display_manager.hpp"  



void draw_line_mask(DisplayManager& display, MPU9250_asukiaaa& gyroSensor);
void gyro_ball(DisplayManager& display, MPU9250_asukiaaa& gyroSensor);


#endif