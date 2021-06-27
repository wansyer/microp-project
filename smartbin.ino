#include <Servo.h>

Servo servo_9;
const int fsrAnalogPin = A0;   
int fsrReading = 0;
const int pingPin = 7;
int ledGreen = 11;
int ledYellow = 12;
int ledRed = 13;
int Minimum = 5;
int Maximum = 10;

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
    long duration, inches, cm;                      // Initialize FSR
    int fsrReading = analogRead(fsrAnalogPin); 
    Serial.print("Analog reading = ");
    Serial.println(fsrReading);
    
    pinMode(pingPin, OUTPUT);`                      // Initialize UDS
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    

    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
    
    //convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    if (100 < cm && cm < 300)
    {
        if (fsrReading < Minimum) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, HIGH);
            delay(3000);
            digitalWrite(ledGreen, LOW);
        }
        else if (Minimum < fsrReading && fsrReading < Maximum) 
        {
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledYellow, HIGH);
            delay(3000);
            digitalWrite(ledYellow, LOW);
        }
        else if (fsrReading > Maximum) 
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
        if (fsrReading < Maximum) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, LOW);
            
            for (angle = 0; angle <= 90; angle += 1) 
            {
                myservo.write(angle);
                delay(15);
            }
            delay(5000);
            for (angle = 90; angle >= 0; angle -= 1) 
            {
                myservo.write(angle);
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
{
break;
}
Serial.println(analogValue);
delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
