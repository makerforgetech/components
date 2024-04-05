/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

/*
 * Useful for outputs. Tested with vibrating module
 */
int outputPin = 23;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(outputPin, HIGH);
  delay(1000);        
  digitalWrite(outputPin, LOW);
  delay(1000);        
}
