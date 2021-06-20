const int fsrAnalogPin = A0;    // pin for sensor
const int pingPin = 7;
const int ledGreen = 13;       // pin for Green LED
const int ledRed = 12;       // pin for Red LED
const int transistor = 2;
const int threshold = 300;   // an arbitrary threshold level that's in the range of the analog input

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode (transistor, OUTPUT);
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;
  int fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // if the distance is less than 3 meter, Green LED is ON
  if (fsrReading < threshold) {
    digitalWrite(ledGreen, HIGH);
    // insert another set of instructions below
    

  } else {
    digitalWrite (transistor, HIGH);
    delay(500);
    digitalWrite (transistor, LOW);
    delay(500);
  }

  // print the analog value:
  Serial.println(fsrReading);
  delay(100);        // delay in between reads for stability
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
