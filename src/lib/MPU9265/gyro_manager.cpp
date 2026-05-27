#include "gyro_manager.hpp"

#include <MPU9250_asukiaaa.h>


bool init_gyro(MPU9250_asukiaaa& mySensor) {
    mySensor.setWire(&Wire);
    
    uint8_t sensorId;
    if (mySensor.readId(&sensorId) != 0) {
        Serial.println("ERR: MPU9250 not found! Check I2C wiring.");
        return false;
    }

    mySensor.beginAccel();
    mySensor.beginGyro();
    mySensor.beginMag();
    
    return true;
}
