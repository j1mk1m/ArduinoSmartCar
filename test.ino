/*Smart Car Project
   James Kim
   07/14/2020

   Description: Four wheel robot car with functions
   Functions:
   1. Obstacle Avoidance: stops before an obstacle, then turns in either direction
   2. Line Tracking: can follow the path of a black line
   3. Remote Control: move according to signals sent through infrared remote, can switch between modes with remote
   4. Light sensor: turns on light if dark

*/

//DC Motors
#include <AFMotor.h>
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);
const int initialSpeed = 150;
const int turnSpeed = 200;






void setup() {
  Serial.begin(9600);

  //DC Motors
  motor1.setSpeed(initialSpeed);
  motor2.setSpeed(initialSpeed);
  motor3.setSpeed(initialSpeed);
  motor4.setSpeed(initialSpeed);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  




}


void loop() {

  //motor4.run(FORWARD);


  
  
  

}
