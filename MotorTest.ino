//DC Motors
#include <AFMotor.h>
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);
const int initialSpeed = 150;
const int turnSpeed = 200;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:

//  //Direction Test
//  motor1.run(FORWARD);
//   motor2.run(FORWARD);
//    motor3.run(FORWARD);
//
//  motor4.run(FORWARD);
//  

  //Speed Test
  
  motor1.setSpeed(initialSpeed);
  motor2.setSpeed(initialSpeed);
  motor3.setSpeed(initialSpeed);
  motor4.setSpeed(initialSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(5000);
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor3.setSpeed(turnSpeed);
  motor4.setSpeed(turnSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(5000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(5000);
  



  //Turn Test
  /*
  //left turn
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor3.setSpeed(turnSpeed);
  motor4.setSpeed(turnSpeed);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(500);
  //right turn
  motor1.setSpeed(turnSpeed);
  motor2.setSpeed(turnSpeed);
  motor3.setSpeed(turnSpeed);
  motor4.setSpeed(turnSpeed);

  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(500);
  */


}
