#include "gyro_stat.hpp"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_Sensor.h>
#include "lib/Display/display_manager.hpp"
#include "include/hw_config.hpp"

static float smoothRoll = 0.0;
static float smoothPitch = 0.0;

void gyro_stat(DisplayManager& display, MPU9250_asukiaaa& gyroSensor) {
    gyroSensor.accelUpdate();

    float aX = gyroSensor.accelX();
    float aY = gyroSensor.accelY();
    float aZ = gyroSensor.accelZ();
    
    float rawRoll = atan2(aY, -aZ) * 180.0 / PI;
    float rawPitch = atan2(-aX, sqrt(aY * aY + aZ * aZ)) * 180.0 / PI;
    
    smoothRoll = (Config::SMOOTHING * rawRoll) + ((1.0 - Config::SMOOTHING) * smoothRoll);
    smoothPitch = (Config::SMOOTHING * rawPitch) + ((1.0 - Config::SMOOTHING) * smoothPitch);
    
    char bufX[16];
    char bufY[16];
    
    snprintf(bufX, sizeof(bufX), "X:  %.1f", smoothRoll);
    snprintf(bufY, sizeof(bufY), "Y: %.1f", smoothPitch);
    
    display.clear();
    display.draw_text(10, Config::CENTER_Y - 8, bufX);
    display.draw_text(10, Config::CENTER_Y + 8, bufY);
    display.render();
}