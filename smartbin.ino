#include <Servo.h>

Servo myservo;
int pos=0;

Servo servo_9;
const int fsrAnalogPin = 0;
int fsrReading;
const int pingPin = 6;
int ledGreen = 12;
int ledYellow = 11;
int ledRed = 13;
const int Minimum = 4.905;
const int Maximum = 9.81;
int fsrVoltage; 
unsigned long fsrResistance;
unsigned long fsrConductance;
long fsrForce; 

void setup() 
{
pinMode(ledGreen, OUTPUT);
pinMode(ledRed, OUTPUT);
pinMode(ledYellow, OUTPUT);
servo_9.attach(9); 
pinMode(fsrAnalogPin, INPUT);
Serial.begin(9600);
}

void loop() 
{
long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(duration);
  Serial.print(" ms ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(1000);
              
fsrReading = analogRead(fsrAnalogPin); 
Serial.print("Analog reading = ");
Serial.println(fsrReading);
  
if (100 < cm && cm < 300){
    fsrReading = analogRead(fsrAnalogPin);
    fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
		if (fsrVoltage == 0){
        Serial.println("No pressure");  
        }
else {       
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
    Serial.print("Conductance in microMhos: ");
    Serial.println(fsrConductance);
    if (fsrConductance <= 1000)
	{
    fsrForce = fsrConductance / 80;
    Serial.print("Force in Newtons: ");
    Serial.println(fsrForce);}
}

    if (fsrForce < Minimum) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);
            delay(3000);
            digitalWrite(ledGreen, LOW);
        }
        else if (Minimum < fsrForce && fsrForce < Maximum) 
        {
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledYellow, HIGH);
            delay(3000);
            digitalWrite(ledYellow, LOW);
        }
        else if (fsrForce > Maximum) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledRed, HIGH);
            delay(3000);
            digitalWrite(ledRed, LOW);
        }
}
    else if (0 < cm && cm < 100)
    {
        if (fsrForce < Maximum) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, LOW);
            
            for (pos = 0; pos <= 90; pos += 1) 
            {
                myservo.write(pos);
            delay(15);
            }
            delay(5000);
            for (pos = 90; pos >= 0; pos -= 1) 
            {
                myservo.write(pos);
            delay(30);
            }
        delay(7000);
        }
        else
        {
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, HIGH);
            delay(1000);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledRed, HIGH);
            delay(1000);
            digitalWrite(ledRed, LOW);
            myservo.write(0);
        }
    }
    else{
        myservo.write(0);
    }
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
return microseconds / 29 / 2;
}
