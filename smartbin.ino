const int fsrAnalogPin = A0;    // pin for sensor
const int transistor = 2;
const int ledGreen = 13;       // pin for Green LED
const int ledRed = 12;       // pin for Red LED
const int threshold = 300;   // an arbitrary threshold level that's in the range of the analog input

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode (transistor, OUTPUT)
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
  int fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);

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
  Serial.println(analogValue);
  delay(100);        // delay in between reads for stability
}
