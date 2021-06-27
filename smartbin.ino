#include <Servo.h>

Servo myservo;
// Define the servo pin:
#define servoPin 9
int angle = 0;
const int fsrAnalogPin = 0;
int fsrReading;
const int pingPin = 6;
int ledGreen = 12;
int ledYellow = 11;
int ledRed = 13;
const int Minimum = 4.905;
const int Maximum = 9.81;
const int Threshold = 9.00;
int fsrVoltage; 
unsigned long fsrResistance;
unsigned long fsrConductance;
long fsrForce; 

void setup() 
{
pinMode(ledGreen, OUTPUT);
pinMode(ledRed, OUTPUT);
pinMode(ledYellow, OUTPUT);
myservo.attach(servoPin);
pinMode(fsrAnalogPin, INPUT);
Serial.begin(9600);
}

void loop() 
{
long duration, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);


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
    myservo.write(0);
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
      myservo.write(0);
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
        if (fsrForce < Threshold) 
        {
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledGreen, LOW);
            
            myservo.write(90);
            delay(5000);
            myservo.write(0);
            delay(1500);
        }
        else if (fsrForce > Threshold)
        {
          myservo.write(0);
            digitalWrite(ledGreen, LOW);
            digitalWrite(ledYellow, LOW);
            digitalWrite(ledRed, HIGH);
            delay(1000);
            digitalWrite(ledRed, LOW);
            digitalWrite(ledRed, HIGH);
            delay(1000);
            digitalWrite(ledRed, LOW);
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
