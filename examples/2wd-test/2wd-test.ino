#include <twowd.h>

TwoWD robot;

boolean isMoving = true;

void setup() {
  // put your setup code here, to run once:
  robot.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
  robot.driveForward(2000);
  delay(2000);
  robot.driveBackward(2000);
  delay(2000);
}
