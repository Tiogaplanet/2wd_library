/* Copyright (C) 2019  Samuel Trassare (https://github.com/tiogaplanet)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
/* This is the implementation of the 2wd robot's API.
*/
#include "twowd.h"


// Number of times that 2wd should try to connet WiFi.
#define TWOWD_MAX_BEGIN_RETRIES 3

// Number of milliseconds to wait between retries.
#define TWOWD_BEGIN_RETRY_WAIT 500

// EEPROM base address.  When reading or writing to EEPROM the user will pass an offset that is added to this base address.
#define TWOWD_BASE_EEPROM_ADDRESS 0x20

// Last addressable address in EEPROM.
#define TWOWD_LAST_EEPROM_ADDRESS 0x2F

// Baud rate for 2wd serial communications.
#define TWOWD_BAUD_RATE 9600

// Hardware setup.

// OLED display width, in pixels.
#define SCREEN_WIDTH 128

// OLED display height, in pixels.
#define SCREEN_HEIGHT 64

// The left motor is connected to pin 4.
#define TWOWD_ENABLE_LEFT 4

// Pin 5 is the pulse-width modulation pin for the left motor.
#define TWOWD_PULSE_LEFT 5

// The right motor is connected to pin 7.
#define TWOWD_ENABLE_RIGHT 7

// Pin 6 is the pulse-width modulation pin for the right motor.
#define TWOWD_PULSE_RIGHT 6

// OLED display address on the I2C bus.
#define OLED_DEVICE_ADDRESS 0x3C

// OLED display dimensions, in pixels.
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins).
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Define an assert mechanism that can be used to log and halt when the user is found to be calling the API incorrectly.
#define TWOWD_ASSERT(EXPRESSION) if (!(EXPRESSION)) mipAssert(__LINE__);

static void twoWDAssert(uint32_t lineNumber)
{
    Serial.print(F("2wd assert: twowd.cpp: "));
        Serial.println(lineNumber);

    while (1)
    {
    }
}



TwoWD::TwoWD()
{
  clear();


}

TwoWD::~TwoWD()
{
    end();
}

void TwoWD::clear()
{
    m_flags = 0;
    m_driveTimer = 0;
    m_speed = TWOWD_MEDIUM_SPEED;
    memset(m_ssid, 0, sizeof(m_ssid));
    memset(m_password, 0, sizeof(m_password));
    memset(m_hostname, 0, sizeof(m_hostname));
}

bool TwoWD::begin()
{
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_DEVICE_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  //delay(2000);
  display.clearDisplay();
  display.display();

  pinMode(TWOWD_ENABLE_LEFT, OUTPUT);
  pinMode(TWOWD_PULSE_LEFT, OUTPUT);
  pinMode(TWOWD_ENABLE_RIGHT, OUTPUT);
  pinMode(TWOWD_PULSE_RIGHT, OUTPUT);
}

bool TwoWD::begin(const char* ssid, const char* password, const char* hostname)
{

}

void TwoWD::end()
{
}

void TwoWD::sleep()
{
}

void TwoWD::turnLeft(uint16_t degrees)
{
}

void TwoWD::turnRight(uint16_t degrees)
{
}

void TwoWD::driveForward()
{
  display.setCursor(0, 20);
  display.println("Forward");
  display.display();
  
  m_flags = TWOWD_FLAG_DRIVE_FORWARD;
  
  digitalWrite(TWOWD_PULSE_LEFT, HIGH);
  analogWrite(TWOWD_ENABLE_LEFT, m_speed);
  digitalWrite(TWOWD_PULSE_RIGHT, HIGH);
  analogWrite(TWOWD_ENABLE_RIGHT, m_speed);
  
  m_isMoving = true;
}

void TwoWD::driveForward(uint16_t time)
{
    if ((m_driveTimer == 0) && (m_flags == TWOWD_FLAG_STOPPED))
    {
       m_driveTimer = millis();
       this->driveForward();
    }

  if (((millis() - m_driveTimer) > time)) {
    this->stop();
    m_driveTimer = 0;
  }
}

void TwoWD::driveBackward()
{
  display.setCursor(0, 20);
  display.println("Backward");
  display.display();
  
  m_flags = TWOWD_FLAG_DRIVE_BACKWARD;
      
  digitalWrite(TWOWD_PULSE_LEFT, LOW);
  analogWrite(TWOWD_ENABLE_LEFT, m_speed);
  digitalWrite(TWOWD_PULSE_RIGHT, LOW);
  analogWrite(TWOWD_ENABLE_RIGHT, m_speed);
    
  m_isMoving = true;
}

void TwoWD::driveBackward(uint16_t time)
{
    if ((m_driveTimer == 0) && (m_flags == TWOWD_FLAG_STOPPED)) {
    m_driveTimer = millis();
    this->driveBackward();
  }

  if (((millis() - m_driveTimer) > time)) {
    this->stop();
    m_driveTimer = 0;
  }
}

void TwoWD::stop()
{  
  analogWrite(TWOWD_ENABLE_LEFT, TWOWD_STOP_SPEED);
  analogWrite(TWOWD_ENABLE_RIGHT, TWOWD_STOP_SPEED);
  
  m_isMoving = false;
  m_flags = TWOWD_FLAG_STOPPED;
  
  display.clearDisplay();
  display.display();
}

boolean TwoWD::isMoving(){
  return m_isMoving;
}

float TwoWD::readDistanceTravelled()
{
}

void TwoWD::resetDistanceTravelled()
{
}

float TwoWD::readBatteryVoltage()
{
}

void TwoWD::setUserData(uint8_t addressOffset, uint8_t userData)
{
}

uint8_t TwoWD::getUserData(uint8_t addressOffset)
{
}
