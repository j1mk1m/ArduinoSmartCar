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
//AF_DCMotor motor1(1, MOTOR12_1KHZ);
//AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);
const int initialSpeed = 150;
const int turnSpeed = 200;

//Servo
#include <Servo.h>
Servo servo1;
int servoPos = 0;

//Ultrasonic Sensor /obstacle avoidance
#define trigPin A0
#define echoPin A1
const int safeDistance = 20;
int path;

//line tracker, infrared sensors
#define leftIR A2
#define rightIR A3
const int lineTrackSpeed = 125;

//light sensor
#define light A4
const int led = 2;
int lightOn = 0;

//IR remote
#include <IRremote.h>
const int ir_rec = A5;
IRrecv irrecv(ir_rec);
decode_results results;

//MODE
int mode;
int prev;





void setup() {
  Serial.begin(9600);

  //DC Motors
  motor3.setSpeed(initialSpeed);
  motor4.setSpeed(initialSpeed);

  motor3.run(RELEASE);
  motor4.run(RELEASE);
  path = 0;

  //Servo
  servo1.attach(10);
  

  //Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //IR sensor
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  //light sensor
  pinMode(light, INPUT);
  pinMode(led, OUTPUT);

  //IR remote
  irrecv.enableIRIn();

  //MODES
  mode = 3; //1 = obstacle avoidance, 2 = line tracking, 3 = IR control (DEFAULT)
  prev = 0;

}




void loop() {
  if (irrecv.decode(&results))
    {
      Serial.println(results.value, HEX);

      if (results.value == 0xFFA25D || results.value == 0xE318261B)
      {
        mode = 1;
        prev = 4;
        Serial.println("Changed to mode 1");

      }
      else if (results.value == 0xFF629D || results.value == 0x511DBB)
      {
        mode = 2;
        prev = 4;
        Serial.println("Changed to mode 2");

      }
      else if (results.value == 0xFFE21D || results.value == 0xEE886D7F)
      {
        mode = 3;
        prev = 4;
        Serial.println("Changed to mode 3");
        Serial.println(mode);

      }
      irrecv.resume();
    }

//  if (analogRead(light) > 400)
//  {
//    digitalWrite(led, HIGH);
//  }
//  else
//  {
//    if (lightOn == 0)
//    {
//      digitalWrite(led, LOW);
//    }
//  }

  //OBSTALCE AVOIDANCE MODE
  if (mode == 1)
  {
    
    if (path == 0)
    {

      if (obstacle() > safeDistance)
      {
        motor3.setSpeed(initialSpeed);
        motor4.setSpeed(initialSpeed);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
      }
      else
      {
        //Serial.println("Obstacle encountered");
        motor3.run(RELEASE);
        motor4.run(RELEASE);

        //Serial.println("Scanning for Route");

        int left = 191;
        int right = 9;
        int increment = 30;
        for (int i = 130; i < 191; i += increment)
        {
          servo1.write(i);
          if (obstacle() > 30)
          {
            if (i < left)
            {
              left = i;
            }
          }
          delay(500);
        }
        for (int i = 70; i > 9; i -= increment)
        {
          servo1.write(i);
          if (obstacle() > 30)
          {
            if (i > right)
            {
              right = i;
            }
          }
          delay(500);
        }
        servo1.write(100);
        delay(500);
        if ((left - 100) < (100 - right))
        {
          path = 2; //left turn
        }
        else
        {
          path = 1; //right turn
        }
      }
    }
    else if (path == 1)
    {
      //Serial.println("Turning Right");
      motor3.setSpeed(turnSpeed);
      motor4.setSpeed(turnSpeed);
      motor3.run(BACKWARD);
      motor4.run(FORWARD);
      //delay(100);

      if (obstacle() > 50)
      {
        path = 0;
      }
    }
    else
    {
      //Serial.println("Turning Left");

      motor3.setSpeed(turnSpeed);
      motor4.setSpeed(turnSpeed);
      motor3.run(FORWARD);
      motor4.run(BACKWARD);
      //delay(100);

      if (obstacle() > 40)
      {
        path = 0;
        //Serial.println("straight");
      }

    }
  }
  else if (mode == 2) //Line tracking mode
  {
    if (digitalRead(leftIR) == 1 && digitalRead(rightIR) != 1)
    {
      //Serial.println("Turning Left");

      motor3.setSpeed(lineTrackSpeed);
      motor4.setSpeed(lineTrackSpeed);

      motor3.run(FORWARD);
      motor4.run(BACKWARD);
      
    }
    else if (digitalRead(leftIR) != 1 && digitalRead(rightIR) == 1)
    {
      //Serial.println("Turning Right");

      motor3.setSpeed(lineTrackSpeed);
      motor4.setSpeed(lineTrackSpeed);
      motor3.run(BACKWARD);
      motor4.run(FORWARD);
      

    }
    else if ((digitalRead(leftIR) != 1 && digitalRead(rightIR) != 1) || (digitalRead(leftIR) == 1 && digitalRead(rightIR) == 1))
    {

      motor3.setSpeed(lineTrackSpeed);
      motor4.setSpeed(lineTrackSpeed);

      motor3.run(FORWARD);
      motor4.run(FORWARD);
      
    }
   
  }
  else //Remote control mode
  {
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    if (irrecv.decode(&results))
    {

      Serial.println(results.value, HEX);

      if (results.value == 0xFFA25D || results.value == 0xE318261B)
      {
        mode = 1;
        prev = 4;

      }
      else if (results.value == 0xFF629D || results.value == 0x511DBB)
      {
        mode = 2;
        prev = 4;

      }
      else if (results.value == 0xFFE21D || results.value == 0xEE886D7F)
      {
        mode = 3;
        prev = 4;

      }
      else if (results.value == 0xFF18E7 || results.value == 0x3D9AE3F7)
      {
        Serial.println("Forward");

        motor3.setSpeed(initialSpeed);
        motor4.setSpeed(initialSpeed);

        motor3.run(FORWARD);
        motor4.run(FORWARD);
        delay(100);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        prev = 0;
      }
      else if (results.value == 0xFF10EF || results.value == 0x8C22657B)
      {
        Serial.println("Turning Left");

        motor3.setSpeed(turnSpeed);
        motor4.setSpeed(turnSpeed);

        motor3.run(FORWARD);
        motor4.run(BACKWARD);
        delay(100);

        motor3.run(RELEASE);
        motor4.run(RELEASE);
        prev = 1;
      }
      else if (results.value == 0xFF5AA5 || results.value == 0x449E79F)
      {
        Serial.println("Turning Right");

        motor3.setSpeed(turnSpeed);
        motor4.setSpeed(turnSpeed);
        motor3.run(BACKWARD);
        motor4.run(FORWARD);

        delay(100);

        motor3.run(RELEASE);
        motor4.run(RELEASE);
        prev = 2;
      }
      else if (results.value == 0xFF4AB5 || results.value == 0x1BC0157B)
      {
        Serial.println("Backward");

        motor3.setSpeed(initialSpeed);
        motor4.setSpeed(initialSpeed);

        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        delay(100);

        motor3.run(RELEASE);
        motor4.run(RELEASE);
        prev = 3;
      }
      else if (results.value == 0xFF38C7 || results.value == 0x488F3CBB)
      {
        if (lightOn == 0)
        {
          digitalWrite(led, HIGH);
          lightOn = 1;
        }
        else
        {
          lightOn = 0;
        }
        prev = 4;
      }
      else if (results.value == 0xFFFFFFFF)
      {
        Serial.println(prev);
        if (prev == 0)
        {
          motor3.setSpeed(initialSpeed);
          motor4.setSpeed(initialSpeed);

          motor3.run(FORWARD);
          motor4.run(FORWARD);
          delay(100);

          motor3.run(RELEASE);
          motor4.run(RELEASE);
        }
        else if (prev == 1)
        {
          motor3.setSpeed(turnSpeed);
          motor4.setSpeed(turnSpeed);

          motor3.run(FORWARD);
          motor4.run(BACKWARD);
          delay(100);

          motor3.run(RELEASE);
          motor4.run(RELEASE);
        }
        else if (prev == 2)
        {
          motor3.setSpeed(turnSpeed);
          motor4.setSpeed(turnSpeed);
          motor3.run(BACKWARD);
          motor4.run(FORWARD);

          delay(100);

          motor3.run(RELEASE);
          motor4.run(RELEASE);
        }
        else if (prev == 3)
        {
          motor3.setSpeed(initialSpeed);
          motor4.setSpeed(initialSpeed);

          motor3.run(BACKWARD);
          motor4.run(BACKWARD);
          delay(100);

          motor3.run(RELEASE);
          motor4.run(RELEASE);
        }
      }
      else
      {
        prev = 4;
      }
      irrecv.resume();
    }
  }
}




//OBSTACLE AVOIDANCE FUNCTIONS
long obstacle ()
{
  long duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration / 29 / 2;
  return cm;
}
