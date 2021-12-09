joint IN1 = 15;
int IN2 = 13;
int ENA = 12;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);

  for (int i = 0; i < 255; i += 20) {
    analogWrite(ENA, i);
    delay(100);
  }

  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  delay(3000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);


  for (int i = 255; i > 0; i -= 20) {
    analogWrite(ENA, i);
    delay(100);
  }

  delay(3000);

  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  delay(3000);

}