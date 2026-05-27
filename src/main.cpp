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

  pinMode(Config::BUZZER_PIN, OUTPUT);
}

static float smoothRoll = 0.0;
static float smoothPitch = 0.0;

const unsigned char car_map[] = {
  0x30, 0x00, 0x78, 0x00, 0xB4, 0x00, 0x30, 0x00, 0x78, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x30, 0x00, 0x78, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x30, 0x00, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char enemy_map[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x15, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x0E, 0x00, 0x00, 0x15, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

struct Enemy {
  float x;
  float y;
  float speed;
};

std::vector<Enemy> enemies;

unsigned long lastSpawnTime = 0;
unsigned long spawnInterval = 1000; 

int playerLives = 3;

void loop() {
  gyroSensor.gyroUpdate();
  gyroSensor.accelUpdate();

  float aX = gyroSensor.accelX();
  float aY = gyroSensor.accelY();
  float aZ = gyroSensor.accelZ();

  float rawRoll = -(atan2(aY, -aZ) * 180.0 / PI);
  smoothRoll = (0.4 * rawRoll) + ((1.0 - 0.4) * smoothRoll);
  int carX = Config::CENTER_X + (smoothRoll * 1); 

  carX = constrain(carX, 0, Config::SCREEN_WIDTH - 16);

  unsigned long currentMillis = millis();

  if (currentMillis - lastSpawnTime >= spawnInterval) {
    lastSpawnTime = currentMillis;
    
    float randomX = random(0, Config::SCREEN_WIDTH - 20); 
    float randomSpeed = random(10, 25) / 10.0;

    enemies.push_back({randomX, -20.0, randomSpeed});
  }

  display.clear();

  int enemyToRemove = -1; 

  if (!enemies.empty()) {
    int enemyCount = (int)enemies.size(); 
    
    for (int i = enemyCount - 1; i >= 0; i--) {
      enemies[i].y += enemies[i].speed;

      display.drawSprite((int)enemies[i].x, (int)enemies[i].y, enemy_map, 20, 20);

      if (enemies[i].x < (carX + 16) &&
          (enemies[i].x + 20) > carX &&
          enemies[i].y < (48 + 16) &&
          (enemies[i].y + 20) > 48) {
            
          enemyToRemove = i;
      }

      if (enemies[i].y > Config::SCREEN_HEIGHT) {
        enemies.erase(enemies.begin() + i);
      }
    }
  }

  if (enemyToRemove != -1) {
    playerLives--;
    enemies.erase(enemies.begin() + enemyToRemove);

    if (playerLives <= 0) {
      enemies.clear();
      playerLives = 3;
      lastSpawnTime = millis();
      delay(1000);
    } else {
      delay(200); 
    }
  }

  for (int i = 0; i < playerLives; i++) {
    display.drawHeart((Config::SCREEN_WIDTH - 10) - (i * 10), 2);
  }

  display.drawSprite(carX, 48, car_map, 16, 16);
  display.render();
}