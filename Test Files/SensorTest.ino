
#include <AFMotor.h>
#define trigPin A0
#define echoPin A1
#define leftIR A2
#define rightIR A3
#define light A4
#define irRec A5
#include <IRremote.h>
const int ir_rec = A5;
IRrecv irrecv(ir_rec);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  
  //Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //IR sensor
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  //light sensor
  pinMode(light, INPUT);
  Serial.begin(9600);

   //IR remote
  irrecv.enableIRIn();
  irrecv.blink13(true);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  //Ultrasonic sensor
  Serial.print("Distance is ");
  Serial.print(distance());
  Serial.println(" cm");
  delay(500);
  */

  //IR sensor
  
  Serial.print("Left IR sensor reads: "); 
  Serial.println(digitalRead(leftIR));
  Serial.print("Right IR sensor reads: ");
  Serial.println(digitalRead(rightIR));
  delay(1000);
  

  //light sensor
  /*
  Serial.print("The brightness is :"); 
  Serial.println(analogRead(light));
  delay(1000);
  */

  //IR remote
  /*
  if (irrecv.decode(&results))
  {
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
  */
  



}

long distance ()
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
