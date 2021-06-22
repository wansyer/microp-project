#include <Servo.h>

Servo servo_9;
const int fsrAnalogPin = A0;    // pin for sensor
int fsrReading = 0;
const int pingPin = 7; //declare pin 7 for Ultrasonic Distance Sensor
int ledGreen = 12;       // pin for Green LED
int ledRed = 13;       // pin for Red LED
int ledYellow = 11;   // pin for Yellow LED
int threshold = 300;   // an arbitrary threshold level that's in the range of the analog input

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  servo_9.attach(9); //set the servo pin 9 as an output pin
  // initialize the force sensor as an input;
  pinMode(fsrAnalogPin, INPUT);
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() 
{
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;
  int fsrReading = analogRead(fsrAnalogPin); //read value from AnalogPin to fsrReading
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
  
  //The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  //Give a shot LOW pulse beforehand to ensure a celan HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  //The same pin is used to read the signal from the PING))): a HIGH pulse
//whose duration is the time (in microseconds) from the sending of the ping
//to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  //convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  
  if (cm<2500)
  {
  // if the distance is less than 3 meter, Green LED is ON
  if (fsrReading < threshold) 
  {
    digitalWrite(ledGreen, HIGH);
    // insert another set of instructions below
    

  }
  else 
  {
    digitalWrite (transistor, HIGH);
    delay(500);
    digitalWrite (transistor, LOW);
    delay(500);
  }
  }
  else if
  {
  
  }
  // print the analog value:
  Serial.println(analogValue);
  delay(100);        // delay in between reads for stability
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
