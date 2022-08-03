#include <AFMotor.h>
#include <Servo.h>
Servo servo1;


void setup() {
  // put your setup code here, to run once:
  servo1.attach(10);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int pos = 100;
  int increment = 33;
  servo1.write(pos);
  
  delay(1000);
  for (int i = 100; i < 200; i += increment)
      {
        servo1.write(i);
        Serial.println(i);
        delay(500);
      }
  for (int i = 100; i > 0; i -= increment)
      {
        servo1.write(i);
        Serial.println(i);
        delay(500);
      }
      
      
        

}
