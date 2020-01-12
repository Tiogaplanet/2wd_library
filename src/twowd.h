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
/* This header file describes the public API that an application can use to communicate with the 2wd robot.
*/
#ifndef TWOWD_H
#define TWOWD_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// A few default speeds.
#define TWOWD_STOP_SPEED   0
#define TWOWD_MEDIUM_SPEED 128
#define TWOWD_FAST_SPEED   255

class TwoWD
{
public:
    // Constructor/Destructors.
    TwoWD();
    ~TwoWD();

    bool begin();
    bool begin(const char* ssid, const char* password, const char* hostname);
    void end();
    void sleep();

    void setSpeed(uint8_t speed);
    uint8_t getSpeed();
    void turnLeft(uint16_t degrees);
    void turnRight(uint16_t degrees);
    void driveForward();
    void driveForwardTime(uint16_t time);
    void driveForwardDistance(uint16_t distance);
    void driveBackward();
    void driveBackwardTime(uint16_t time);
    void driveBackwardDistance(uint16_t distance);
    void stop();
    boolean isMoving();

    float readDistanceTravelled();
    void  resetDistanceTravelled();

protected:
    void clear();
    void clearDisplay();

    // Bits that can be set in m_flags bitfield.
    enum FlagBits
    {
        TWOWD_FLAG_STOPPED        = 0,
        TWOWD_FLAG_DRIVE_FORWARD  = (1 << 0),
        TWOWD_FLAG_DRIVE_BACKWARD = (1 << 1),
        TWOWD_FLAG_TURN_LEFT      = (1 << 2),
        TWOWD_FLAG_TURN_RIGHT     = (1 << 3)
    };

    uint8_t       m_flags;
    unsigned long m_driveTimer;
    uint8_t       m_speed;
    boolean       m_isMoving;
    char          m_ssid[32];
    char          m_password[64];
    char          m_hostname[63];

    Adafruit_SSD1306 *m_oled;
};

#endif // TWOWD_H
