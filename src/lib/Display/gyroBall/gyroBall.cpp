#include "gyroBall.hpp"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>

#include "include/hw_config.hpp"
#include "lib/Display/display_manager.hpp"

#include <vector>

static float smoothRoll = 0.0;
static float smoothPitch = 0.0;

void draw_line_mask(DisplayManager& display, MPU9250_asukiaaa& gyroSensor) {
    std::vector<int> degX = { 15, 45, 80 };
    std::vector<int> degY = { 15, 60 };
    
    for ( auto& el : degX ) {
      int lineXd = Config::CENTER_X - (el * Config::SENSITIVITY);
      int lineX =  Config::CENTER_X + (el * Config::SENSITIVITY);
      display.draw_line(lineX, 0, lineX, Config::SCREEN_HEIGHT);
      display.draw_line(lineXd, 0, lineXd, Config::SCREEN_HEIGHT);
    }
    for ( auto& el : degY ) {
      int lineYd = Config::CENTER_Y - (el * Config::SENSITIVITY);
      int lineY =  Config::CENTER_Y + (el * Config::SENSITIVITY);
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
        smoothRoll = (Config::SMOOTHING * rawRoll) + ((1.0 - Config::SMOOTHING) * smoothRoll);
        smoothPitch = (Config::SMOOTHING * rawPitch) + ((1.0 - Config::SMOOTHING) * smoothPitch);
        int ballX = Config::CENTER_X + (smoothRoll * Config::SENSITIVITY);
        int ballY = Config::CENTER_Y + (-smoothPitch * Config::SENSITIVITY);
    
        ballX = constrain(ballX, 3, 125); 
        ballY = constrain(ballY, 3, 61);
    
        Serial.println(rawRoll);
        Serial.println(rawPitch);
    
        display.clear();
        draw_line_mask(display, gyroSensor);
        if (abs(Config::CENTER_X-ballX) <= 3  && abs(Config::CENTER_Y-ballY) <= 3) display.draw_circle(ballX, ballY, 5, true);
        else display.draw_circle(ballX, ballY, 5, false);
        display.render();
      }
}