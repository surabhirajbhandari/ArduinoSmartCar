// This is the code for the car

#include <Arduino.h>
#include <Servo.h>

Servo ESC; // This is the ESC that controls the back 2 wheels
Servo Steering; // This is the front servo that steers the car

int speed; // Stores the value of the gyro's front/back movement
int turn; // Stores the value of the gyro's left/right movement

void setup()
{
  ESC.attach(9, 1000, 2000); // Pin #, min pulse width, max pulse width
  Steering.attach(8, 1000, 2000); // Pin #, min pulse width, max pulse width

}

void loop()
{
// speed = whatever the input from the gyro for front/back is
// turn = whatever the input from the gyro for left/right is
speed = map(speed, 0,0, 0, 180); // Need the gyro min max output
turn = map(turn, 0, 0, 0, 180);
ESC.write(speed);
Steering.write(turn);
}
