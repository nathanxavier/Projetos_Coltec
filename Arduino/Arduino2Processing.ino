void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Sending a 'Hello, world!'
  Serial.println("Hello, world!");
  // Take a time and relax!
  delay(100);
}
