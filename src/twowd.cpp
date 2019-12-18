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

// Hardware settings.

// Baud rate for 2wd serial communications.
#define TWOWD_BAUD_RATE 9600

// OLED display address on the I2C bus.
#define OLED_DEVICE_ADDRESS 0x3C

// OLED display does not have a reset pin.
#define OLED_RESET -1

// OLED display width, in pixels.
#define SCREEN_WIDTH 128

// OLED display height, in pixels.
#define SCREEN_HEIGHT 64

// Note: The PHASE and ENABLE comments below come from documentation at https://www.pololu.com/product/2135.
// Another note: Considering a different motor driver with a higher continuous output current.
// The PHASE pin determines the motor direction.
#define TWOWD_PHASE_LEFT 4

// The ENABLE pin can be supplied with a PWM signal to control the motor speed.
#define TWOWD_ENABLE_LEFT 5

// The PHASE pin determines the motor direction.
#define TWOWD_PHASE_RIGHT 7

// The ENABLE pin can be supplied with a PWM signal to control the motor speed.
#define TWOWD_ENABLE_RIGHT 6



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins).
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



// Define an assert mechanism that can be used to log and halt when the user is found to be calling the API incorrectly.
#define TWOWD_ASSERT(EXPRESSION) if (!(EXPRESSION)) twoWDAssert(__LINE__);

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

   if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_DEVICE_ADDRESS))
   {
      Serial.println(F("Failed to initialize OLED display."));
   }
   display.clearDisplay();
   display.display();
   
   pinMode(TWOWD_PHASE_LEFT, OUTPUT);
   pinMode(TWOWD_ENABLE_LEFT, OUTPUT);
   pinMode(TWOWD_PHASE_RIGHT, OUTPUT);
   pinMode(TWOWD_ENABLE_RIGHT, OUTPUT);
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
  
   // Set both motors for forward movement.
   digitalWrite(TWOWD_PHASE_LEFT, HIGH);
   digitalWrite(TWOWD_PHASE_RIGHT, HIGH);
   
   // Start forward movement by writing the speed value onto the ENABLE pins.
   analogWrite(TWOWD_ENABLE_LEFT, m_speed);
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

    if (((millis() - m_driveTimer) > time) && (m_flags == TWOWD_FLAG_DRIVE_FORWARD)) 
    {
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

   // Set both motors for backward movement.
   digitalWrite(TWOWD_PHASE_LEFT, LOW);
   digitalWrite(TWOWD_PHASE_RIGHT, LOW);

   // Start backward movement by writing the speed value onto the ENABLE pins.
   analogWrite(TWOWD_ENABLE_LEFT, m_speed);
   analogWrite(TWOWD_ENABLE_RIGHT, m_speed);

   m_isMoving = true;
}

void TwoWD::driveBackward(uint16_t time)
{
   if ((m_driveTimer == 0) && (m_flags == TWOWD_FLAG_STOPPED))
   {
      m_driveTimer = millis();
      this->driveBackward();
   }

   if (((millis() - m_driveTimer) > time) && (m_flags == TWOWD_FLAG_DRIVE_BACKWARD))
   {
      this->stop();
      m_driveTimer = 0;
   }
}

void TwoWD::stop()
{  
   // Stop movement by writing zeros onto the ENABLE pins for both motors.
   analogWrite(TWOWD_ENABLE_LEFT, TWOWD_STOP_SPEED);
   analogWrite(TWOWD_ENABLE_RIGHT, TWOWD_STOP_SPEED);

   m_isMoving = false;
   m_flags = TWOWD_FLAG_STOPPED;
  
   display.clearDisplay();
   display.display();
}

boolean TwoWD::isMoving()
{
   return m_isMoving;
}

float TwoWD::readDistanceTravelled()
{
   
}

void TwoWD::resetDistanceTravelled()
{
   
}
