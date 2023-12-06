int relayPin = 2; // Connect this pin to the relay signal pin

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Activate the relay (and solenoid motor) for 2 seconds
  digitalWrite(relayPin, HIGH);
  delay(5000);
  
  // Deactivate the relay (and solenoid motor) for 2 seconds
  digitalWrite(relayPin, LOW);
  delay(5000);
}
