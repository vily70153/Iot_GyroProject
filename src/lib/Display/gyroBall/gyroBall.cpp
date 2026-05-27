#include "gyroBall.hpp"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>

#include "include/hw_config.hpp"
#include "lib/Display/display_manager.hpp"

#include <vector>

const int CENTER_X = 64;
const int CENTER_Y = 32;
const float SENSITIVITY = 0.6;
const float SMOOTHING = 0.15;
float smoothRoll = 0.0;
float smoothPitch = 0.0;

void draw_line_mask(DisplayManager& display, MPU9250_asukiaaa& gyroSensor) {
    std::vector<int> degX = { 15, 45, 80 };
    std::vector<int> degY = { 15, 60 };
    
    for ( auto& el : degX ) {
      int lineXd = CENTER_X - (el * SENSITIVITY);
      int lineX =  CENTER_X + (el * SENSITIVITY);
      display.draw_line(lineX, 0, lineX, Config::SCREEN_HEIGHT);
      display.draw_line(lineXd, 0, lineXd, Config::SCREEN_HEIGHT);
    }
    for ( auto& el : degY ) {
      int lineYd = CENTER_Y - (el * SENSITIVITY);
      int lineY =  CENTER_Y + (el * SENSITIVITY);
      display.draw_line(0, lineY, Config::SCREEN_WIDTH, lineY);
      display.draw_line(0, lineYd, Config::SCREEN_WIDTH, lineYd);
    }
  }

void gyro_ball(DisplayManager& display, MPU9250_asukiaaa& gyroSensor) {
    if (gyroSensor.accelUpdate() == 0) {
    
        float aX = gyroSensor.accelX();
        float aY = gyroSensor.accelY();
        float aZ = gyroSensor.accelZ();
        
        float rawRoll = atan2(aY, -aZ) * 180.0 / PI;
        float rawPitch = atan2(-aX, sqrt(aY * aY + -aZ * -aZ)) * 180.0 / PI;
        smoothRoll = (SMOOTHING * rawRoll) + ((1.0 - SMOOTHING) * smoothRoll);
        smoothPitch = (SMOOTHING * rawPitch) + ((1.0 - SMOOTHING) * smoothPitch);
        int ballX = CENTER_X + (smoothRoll * SENSITIVITY);
        int ballY = CENTER_Y + (-smoothPitch * SENSITIVITY);
    
        ballX = constrain(ballX, 3, 125); 
        ballY = constrain(ballY, 3, 61);
    
        Serial.println(rawRoll);
        Serial.println(rawPitch);
    
        display.clear();
        draw_line_mask(display, gyroSensor);
        if (abs(CENTER_X-ballX) <= 3  && abs(CENTER_Y-ballY) <= 3) display.draw_circle(ballX, ballY, 5, true);
        else display.draw_circle(ballX, ballY, 5, false);
        display.render();
      }
}